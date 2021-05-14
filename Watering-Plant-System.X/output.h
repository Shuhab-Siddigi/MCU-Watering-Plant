#ifndef LED_H_
#define LED_H_


#include "registerBits.h"


typedef struct
{
    volatile uint16_t*  TRIS; //Pointer to &PORTx
    volatile uint16_t*  LAT;  //Pointer to &LATx
    uint16_t PIN;             // The Dy port for PORTx.Dy
} OUTPUT;

extern OUTPUT output;

void init_output(OUTPUT output);
void output_SetDigitalOutput(OUTPUT output);
void output_SetLow(OUTPUT output);
void output_SetHigh(OUTPUT output);
void output_Toggle(OUTPUT output);

#endif /* LED_H_ */

