#include "floatswitch.h"

 void floatswitchCallbackISR()
{
    LED1_Toggle();
}


void __attribute__ ( ( interrupt, no_auto_psv ) ) _INT0Interrupt(void)
{
	floatswitchCallbackISR();

    floatswitchFlagClearISR();
}

void init_floatswitch()
{
    floatswitch_FlagClearISR();   
    floatswitch_SetFalingEdge();
    floatswitch_InterruptEnable();
    floatswitch_EnableISR();
}