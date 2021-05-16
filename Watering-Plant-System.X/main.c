//#include "configuration.h"
#include "input.h"
#include "output.h"
#include "floatswitch.h"
#include "adc.h"
#include "uart1.h"
#include <stdio.h>
 #include <stdlib.h>

//#include "mcc_generated_files/system.h"
//#include "mcc_generated_files/uart1.h"


/*BTN btn1;
LED led1;
LED led2;
 * */

/*BTN btn1 = { &TRISA, &PORTC, 8};  // TRISx, PORTx, Dx
LED led1 = { &TRISA, &LATA, 10}; // PORTx, LATx, Dx
LED led2 = { &TRISA, &LATA, 9};  // PORTx, LATx, Dx


void floatswitchCB()
{
    led_Toggle(led2);
}

int main()
{
    led_init(led1);
    led_init(led2);
    btn_init(btn1);
    //set_floatswitchCallbackISR(&floatswitchCB);
    init_floatswitch(&floatswitchCB);

    uint16_t btnState;
    
    
    while (1)
    {
        //led_SetHigh(led1);
        //led_SetHigh(led2);
        btnState = btn_GetValue(btn1);
        
        if(btnState == 1)
        {
            led_SetHigh(led1);
        }
        else
        {
            led_SetLow(led1);
        }
    }

    return 0;
}
*/

// USED IN libpic30 
#define SYS_FREQ 4000000UL //Clock Frequency
#define FCY (SYS_FREQ/2) //Cycle Frequency
// This library is used for delay functions

#include <libpic30.h>
        
OUTPUT motor = {&TRISB, &LATB, 3};
OUTPUT led1 = {&TRISA, &LATA, 10}; // PORTx, LATx, Dx
INPUT floatswitch = {&TRISB, &PORTB, 10};

int floatswitchFlag;

void floatswitchCB()
{
    floatswitchFlag ^= 1;
    if(floatswitchFlag == 0)
    {
        output_SetLow(led1);
    }
    else
    {
        output_Toggle(led1);
    }
}

/*void ReadCallback(uint8_t n, uint8_t * msg, uint8_t msgLength)
{
    uint16_t i;
	printf("Raw UART data received: ");
	for (i=0; i<msgLength; i++)
		printf( "%02x ", msg[i] );
	printf("\r\n");
}
*/

/*
int main()
{
    init_output(motor);
    init_output(led1);
    init_floatswitch(&floatswitchCB);
    init_input(floatswitch);
    init_adc();
    SYSTEM_Initialize();
    //UART_Initialize();

    floatswitchFlag = input_GetValue(floatswitch) == 1 ? 1 : 0;
    
    while (1)
    {
        
        if(floatswitchFlag == 1 && ADC_GetConversion(MOISTURESENSOR))
        {
            output_SetHigh(motor);
        }
        else
        {
            output_SetLow(motor);
        }
    }

    return 0;
}
*/

int main(void)
{
    int input = 0;
    uint8_t byte = 0xFF;
    // initialize the device
    //SYSTEM_Initialize();
    UART_Initialize();

    while (1)
    {
        //inputLength = UART1_RxDataAvailable();
        /*if(UART_ReadFlag())
        {
            while(byte != '\r')
            {
                byte = UART1_Read();
            }
            byte = 0xFF;
            //UART_WriteMessage("hello\r");
            UART_WriteMessage("10\n");
        }
        */
        UART_WriteMessage("20");
        UART_WriteMessage("20\r");
        UART_WriteMessage("30\n");
        UART_WriteMessage("40\n\r");
        __delay_ms(500);
    }

    return 1;
}