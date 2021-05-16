//#include "configuration.h"
#include "input.h"
#include "output.h"
#include "floatswitch.h"
#include "adc.h"
#include "uart1.h"
#include <stdio.h>
#include <stdlib.h>


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
        output_SetHigh(led1);
    }
}

int adcHigh = 800;
int adcLow = 40;
int adcFlag = 0;
int adcValue;
double adcConverted;
char adcString[5];

char byte = 0xFF;
uint8_t byteArray[3];
int byteArrayIndex = 0;

int main(void)
{
    init_output(motor);
    init_output(led1);
    init_floatswitch(&floatswitchCB);
    init_input(floatswitch);
    init_adc();
    UART_Initialize();

    floatswitchFlag = input_GetValue(floatswitch) == 1 ? 1 : 0;
    
    while (1)
    {
        
        //adcValue = ADC_GetConversion(MOISTURESENSOR);
        adcValue = ADC_GetConversion(POT);
        adcConverted = ((double)adcValue/1024)*100;

        sprintf(adcString, "%.0f\n\r\0", adcConverted);
        
        if(adcValue < adcLow)
        {
            adcFlag = 1;
        } else if(adcValue > adcHigh)
        {
            adcFlag = 0;
        }
        if(floatswitchFlag == 1 && adcFlag == 1)
        {
            output_SetHigh(motor);
        }
        else 
        {
            output_SetLow(motor);
        }
        UART_WriteMessage(adcString);
        while(byteArrayIndex != 2){
            byte = UART1_Read();
            //byte = U1RXREG;
            if(byte > 33 && byte < 58){
                byteArray[byteArrayIndex] = byte;
                byteArrayIndex++;
            }
        }
        byteArray[3] = '\0';
        byteArray[0] = (byteArray[0]-48)*10;
        byteArray[1] = byteArray[1]-48;
        adcLow = byteArray[0] + byteArray[1];
        __delay_ms(600);
    }

    return 1;
}