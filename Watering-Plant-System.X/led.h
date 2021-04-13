#ifndef LED_H_
#define LED_H_


#include "constants.h"

#define LED1_SetDigitalOutput() (_TRISA9 = OUTPUT)
#define LED1_SetLow()           (_LATA9 = LOW)
#define LED1_SetHigh()          (_LATA9 = HIGH)

#define LED2_SetDigitalOutput() (_TRISA10 = OUTPUT)
#define LED2_SetLow()           (_LATA10 = LOW)
#define LED2_SetHigh()          (_LATA10 = HIGH)

#define LEDRED_SetDigitalOutput() (_TRISC5 = OUTPUT)
#define LEDRED_SetLow()           (_LATC5 = LOW)
#define LEDRED_SetHigh()          (_LATC5 = HIGH)


void init_led();

#endif /* LED_H_ */

