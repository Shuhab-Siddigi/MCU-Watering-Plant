#include <stdbool.h>
#include <stdint.h>
#include <stddef.h>
#include "xc.h"
#include "uart.h"

#define UART_BUFFER_SIZE (8+1)

static uint8_t * volatile rxTail;
static uint8_t *rxHead;
static uint8_t *txTail;
static uint8_t * volatile txHead;
static bool volatile rxOverflowed;
static uint8_t txQueue[UART_BUFFER_SIZE];
static uint8_t rxQueue[UART_BUFFER_SIZE];

void (*UART_TxCallback)();
void (*UART_RxCallback)();


int uartFlag = 0;

int UART_ReadFlag()
{
    return uartFlag;
}

void UART_WriteMessage( uint8_t *buffer)
{
    while(*buffer != '\0')
    {
        UART_Write(*buffer++);
    } 
}

void UART_Initialize(void)
{
    IEC0bits.U1TXIE = 0;
    IEC0bits.U1RXIE = 0;

    // STSEL 1; IREN disabled; PDSEL 8N; UARTEN enabled; RTSMD disabled; USIDL disabled; WAKE disabled; ABAUD disabled; LPBACK disabled; BRGH enabled; URXINV disabled; UEN TX_RX; 
    // Data Bits = 8; Parity = None; Stop Bits = 1;
    U1MODE = (0x8008 & ~(1<<15));  // disabling UART ON bit
    // UTXISEL0 TX_ONE_CHAR; UTXINV disabled; URXEN disabled; OERR NO_ERROR_cleared; URXISEL RX_ONE_CHAR; UTXBRK COMPLETED; UTXEN disabled; ADDEN disabled; 
    U1STA = 0x00;
    // BaudRate = 9600; Frequency = 2000000 Hz; U1BRG 51; 
    U1BRG = 0x33;
    /*// BaudRate = 115200; Frequency = 2000000 Hz; U1BRG 3; 
    U1BRG = 0x03;
    */
    // ADMADDR 0; ADMMASK 0; 
    U1ADMD = 0x00;
    // T0PD 1 ETU; PTRCL T0; TXRPT Retransmits the error byte once; CONV Direct; SCEN disabled; 
    U1SCCON = 0x00;
    // TXRPTIF disabled; TXRPTIE disabled; WTCIF disabled; WTCIE disabled; PARIE disabled; GTCIF disabled; GTCIE disabled; RXRPTIE disabled; RXRPTIF disabled; 
    U1SCINT = 0x00;
    // GTC 0; 
    U1GTC = 0x00;
    // WTCL 0; 
    U1WTCL = 0x00;
    // WTCH 0; 
    U1WTCH = 0x00;
    
    txHead = txQueue;
    txTail = txQueue;
    rxHead = rxQueue;
    rxTail = rxQueue;
   
    rxOverflowed = false;

    IEC0bits.U1RXIE = 1;
    
    //Make sure to set LAT bit corresponding to TxPin as high before UART initialization
    U1MODEbits.UARTEN = 1;   // enabling UART ON bit
    U1STAbits.UTXEN = 1;
}

/**
    Maintains the driver's transmitter state machine and implements its ISR
*/

void UART_SetRxInterruptHandler(void (* interruptHandler)(void))
{
    if(interruptHandler != NULL)
    {
        UART_RxCallback = interruptHandler;
    }
}

void UART_SetTxInterruptHandler(void (* interruptHandler)(void))
{
    if(interruptHandler != NULL)
    {
        UART_TxCallback = interruptHandler;
    }
}

void __attribute__ ( ( interrupt, no_auto_psv ) ) _U1TXInterrupt ( void )
{
    if(UART_TxCallback != NULL)
    {
        (*UART_TxCallback)();
    }

    if(txHead == txTail)
    {
        IEC0bits.U1TXIE = 0;
    }
    else
    {
        IFS0bits.U1TXIF = 0;

        while(!(U1STAbits.UTXBF == 1))
        {
            U1TXREG = *txHead++;

            if(txHead == (txQueue + UART_BUFFER_SIZE))
            {
                txHead = txQueue;
            }

            // Are we empty?
            if(txHead == txTail)
            {
                break;
            }
        }
    }
}


void __attribute__ ( ( interrupt, no_auto_psv ) ) _U1RXInterrupt( void )
{
    if(UART_RxCallback != NULL)
    {
        (*UART_RxCallback)();   
    }

    IFS0bits.U1RXIF = 0;
	
    while((U1STAbits.URXDA == 1))
    {
        *rxTail = U1RXREG;
        if(*rxTail == '\r')
        {
            uartFlag++;
        }
        // Will the increment not result in a wrap and not result in a pure collision?
        // This is most often condition so check first
        if ( ( rxTail    != (rxQueue + UART_BUFFER_SIZE-1)) &&
             ((rxTail+1) != rxHead) )
        {
            rxTail++;
        } 
        else if ( (rxTail == (rxQueue + UART_BUFFER_SIZE-1)) &&
                  (rxHead !=  rxQueue) )
        {
            // Pure wrap no collision
            rxTail = rxQueue;
        } 
        else // must be collision
        {
            rxOverflowed = true;
        }
    }
}

void __attribute__ ( ( interrupt, no_auto_psv ) ) _U1ErrInterrupt( void )
{
    if ((U1STAbits.OERR == 1))
    {
        U1STAbits.OERR = 0;
    }
    
    IFS4bits.U1ERIF = 0;
}

uint8_t UART_Read()
{
    uint8_t data = 0;

    while (rxHead == rxTail )
    {
    }
    
    data = *rxHead;
    
    if(data == '\r')
    {
        uartFlag--;
    }

    rxHead++;

    if (rxHead == (rxQueue + UART_BUFFER_SIZE))
    {
        rxHead = rxQueue;
    }
    return data;
}

void UART_Write(uint8_t byte)
{
    while(UART_IsTxReady() == 0)
    {
    }

    *txTail = byte;

    txTail++;
    
    if (txTail == (txQueue + UART_BUFFER_SIZE))
    {
        txTail = txQueue;
    }

    IEC0bits.U1TXIE = 1;
}


bool UART_IsRxReady()
{    
    return !(rxHead == rxTail);
}

bool UART_IsTxReady()
{
    uint16_t size;
    uint8_t *snapshot_txHead = (uint8_t*)txHead;
    
    if (txTail < snapshot_txHead)
    {
        size = (snapshot_txHead - txTail - 1);
    }
    else
    {
        size = ( UART_BUFFER_SIZE - (txTail - snapshot_txHead) - 1 );
    }
    
    return (size != 0);
}