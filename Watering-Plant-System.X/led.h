#ifndef LED_H_
#define LED_H_


#include "constants.h"

#define LEDRED_SetDigitalOutput() (_TRISC5 = OUTPUT)
#define LEDRED_SetLow()           (_LATC5 = LOW)
#define LEDRED_SetHigh()          (_LATC5 = HIGH)
#define LEDRED_Toggle()           (_LATC5 ^= 1)

#define LEDGREEN_SetDigitalOutput() (_TRISC6 = OUTPUT)
#define LEDGREEN_SetLow()           (_LATC6 = LOW)
#define LEDGREEN_SetHigh()          (_LATC6 = HIGH)
#define LEDGREEN_Toggle()           (_LATC6 ^= 1)

#define LEDBLUE_SetDigitalOutput() (_TRISC7 = OUTPUT)
#define LEDBLUE_SetLow()           (_LATC7 = LOW)
#define LEDBLUE_SetHigh()          (_LATC7 = HIGH)
#define LEDBLUE_Toggle()           (_LATC7 ^= 1)

#define LED1_SetDigitalOutput() (_TRISA9 = OUTPUT)
#define LED1_SetLow()           (_LATA9 = LOW)
#define LED1_SetHigh()          (_LATA9 = HIGH)
#define LED1_Toggle()           (_LATA9 ^= 1)

#define LED2_SetDigitalOutput() (_TRISA10 = OUTPUT)
#define LED2_SetLow()           (_LATA10 = LOW)
#define LED2_SetHigh()          (_LATA10 = HIGH)
#define LED2_Toggle()           (_LATA10 ^= 1)

void init_led();

#endif /* LED_H_ */

