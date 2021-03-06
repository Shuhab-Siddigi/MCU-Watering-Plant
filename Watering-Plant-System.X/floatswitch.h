#ifndef FLOATSWITCH_H_
#define	FLOATSWITCH_H_


//#include "constants.h"
#include "registerBits.h"


void set_floatswitchCallback(void(*cb )());
void init_floatswitch(void(*cb )());


#define floatswitch_FlagClearISR()     (IFS0bits.INT0IF = 0)

#define floatswitch_InterruptDisable()  (IEC0bits.INT0IE = 0)
#define floatswitch_InterruptEnable()   (IEC0bits.INT0IE = 1)

#define floatswitch_SetFalingEdge()     (INTCON2bits.INT0EP = 1)
#define floatswitch_SetRisingEdge()     (INTCON2bits.INT0EP = 0)

#define floatswitch_DisableISR()        (IPC0bits.INT0IP = 0)
#define floatswitch_EnableISR()         (IPC0bits.INT0IP = 1)

#endif	/* FLOATSWITCH_H_ */