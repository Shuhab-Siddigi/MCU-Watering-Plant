/*
 * File:   main.c
 * Author: shuhabsiddigi
 *
 * Created on April 8, 2021, 12:01 PM
 */

//#include "configuration.h"
#include "led.h"
#include "button.h"
#include "floatswitch.h"
#include "adc.h"

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
        
LED motor = {&TRISB, &LATB, 10};
LED led1 = {&TRISA, &LATA, 10}; // PORTx, LATx, Dx

int floatswitchFlag = 0;

void floatswitchCB()
{
    floatswitchFlag ^= 1;
    led_Toggle(led1);
}

int main()
{
    init_led(motor);
    init_led(led1);
    init_floatswitch(&floatswitchCB);
    while (1)
    {
        if(floatswitchFlag == 0)
        {
            //led_SetHigh(motor);
        }
        else
        {
            led_SetLow(motor);
        }
        
        //__delay_ms(300);
    }

    return 0;
}


