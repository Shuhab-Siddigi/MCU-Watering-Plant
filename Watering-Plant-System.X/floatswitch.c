#include "floatswitch.h"

#include "ext_int.h"
#include "pin_manager.h"

 void floatswitchCallbackISR()
{
     LED10_Toggle();
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