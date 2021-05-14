#include <stdbool.h>
#include <stdint.h>
#include <stddef.h>
#include "xc.h"
#include "uart.h"

void (*UART_TxCallback)();
void (*UART_RxCallback)();

/**
  Section: Driver Interface
*/

void UART_Initialize(void)
{
    IEC0bits.U1TXIE = 0;
    IEC0bits.U1RXIE = 0;

    // STSEL 1; IREN disabled; PDSEL 8N; UARTEN enabled; RTSMD disabled; USIDL disabled; WAKE disabled; ABAUD disabled; LPBACK disabled; BRGH enabled; URXINV disabled; UEN TX_RX; 
    // Data Bits = 8; Parity = None; Stop Bits = 1;
    U1MODE = (0x8008 & ~(1<<15));  // disabling UART ON bit
    // UTXISEL0 TX_ONE_CHAR; UTXINV disabled; URXEN disabled; OERR NO_ERROR_cleared; URXISEL RX_ONE_CHAR; UTXBRK COMPLETED; UTXEN disabled; ADDEN disabled; 
    U1STA = 0x00;
    /*// BaudRate = 9600; Frequency = 2000000 Hz; U1BRG 51; 
    U1BRG = 0x33;
    */
    // BaudRate = 115200; Frequency = 2000000 Hz; U1BRG 3; 
    U1BRG = 0x03;
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

    IEC0bits.U1RXIE = 1;
    
    //Make sure to set LAT bit corresponding to TxPin as high before UART initialization
    U1MODEbits.UARTEN = 1;   // enabling UART ON bit
    U1STAbits.UTXEN = 1;
}

/**
    Maintains the driver's transmitter state machine and implements its ISR
*/

void UART_SetTxInterruptHandler(void (* interruptHandler)(void))
{
    if(interruptHandler != NULL)
    {
        UART_TxCallback = interruptHandler;
    }
} 

void UART_SetRxInterruptHandler(void (* interruptHandler)(void))
{
    if(interruptHandler != NULL)
    {
        UART_RxCallback = interruptHandler;
    }
}

void __attribute__ ( ( interrupt, no_auto_psv ) ) _U1TXInterrupt ( void )
{
    if(UART_TxCallback != NULL)
    {
        (*UART_TxCallback)();
    }

    IEC0bits.U1TXIE = 0;
}


void __attribute__ ( ( interrupt, no_auto_psv ) ) _U1RXInterrupt( void )
{
    if(UART_RxCallback != NULL)
    {
        (*UART_RxCallback)();
    }

    IFS0bits.U1RXIF = 0;
}

void __attribute__ ( ( interrupt, no_auto_psv ) ) _U1ErrInterrupt( void )
{
    if ((U1STAbits.OERR == 1))
    {
        U1STAbits.OERR = 0;
    }
    
    IFS4bits.U1ERIF = 0;
}