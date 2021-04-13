/*
 * File:   floatswitch.c
 * Author: shuhabsiddigi
 *
 * Created on April 13, 2021, 12:01 PM
 */

#include "floatswitch.h"
#include "led.h"

void init_floatswitch()
{
    floatswitch_FlagClearISR();   
    floatswitch_SetFalingEdge();
    floatswitch_InterruptEnable();
    floatswitch_EnableISR();
}


 
void floatswitch_CallbackISR(){
    LED2_Toggle();
}

void __attribute__ ( ( interrupt, no_auto_psv ) ) _INT0Interrupt(void)
{
	floatswitch_CallbackISR();

    floatswitch_FlagClearISR();
}
