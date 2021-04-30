#ifndef LED_H_
#define LED_H_


#include "registerBits.h"


typedef struct
{
    volatile uint16_t*  TRIS; //Pointer to &PORTx
    volatile uint16_t*  LAT;  //Pointer to &LATx
    uint16_t LED;             // The Dy port for PORTx.Dy
} LED;

extern LED led;

void led_init(LED led);
void led_SetDigitalOutput(LED led);
void led_SetLow(LED led);
void led_SetHigh(LED led);
void led_Toggle(LED led);

#endif /* LED_H_ */

