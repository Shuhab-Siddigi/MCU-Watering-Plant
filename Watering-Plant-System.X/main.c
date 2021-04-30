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

/*BTN btn1;
LED led1;
LED led2;
 * */

BTN btn1 = { &TRISA, &PORTC, 8};  // TRISx, PORTx, Dx
LED led1 = { &TRISA, &LATA, 10}; // PORTx, LATx, Dx
LED led2 = { &TRISA, &LATA, 9};  // PORTx, LATx, Dx


void floatswitchCB()
{
    led_Toggle(led2);
}

int main()
{
    PORTC;
    /*BTN btn1 = { &TRISA, &PORTC, 8};  // TRISx, PORTx, Dx
    LED led1 = { &TRISA, &LATA, 10}; // PORTx, LATx, Dx
    LED led2 = { &TRISA, &LATA, 9};  // PORTx, LATx, Dx
     * */
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


