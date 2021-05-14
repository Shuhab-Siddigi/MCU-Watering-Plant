#include <stdbool.h>
#include <stdint.h>
#include <stddef.h>

#include "floatswitch.h"
//#include "led.h"

void (*FloatswitchCallback)(void);

void init_floatswitch(void(*cb )())
{
    floatswitch_FlagClearISR();   
    floatswitch_SetFalingEdge();
    floatswitch_InterruptEnable();
    floatswitch_EnableISR();
    
    if(cb != NULL)
    {
        FloatswitchCallback = cb;
    }
}

void set_floatswitchCallback(void(*cb )())
{
    FloatswitchCallback = cb;
}

void __attribute__ ( ( interrupt, no_auto_psv ) ) _INT0Interrupt(void)
{
    if(FloatswitchCallback != NULL)
    {
        (*FloatswitchCallback)();
    }
    
    floatswitch_FlagClearISR();
}
