#ifndef OUTPUT_H_
#define OUTPUT_H_


#include "registerBits.h"


typedef struct
{
    volatile uint16_t*  TRIS; //Pointer to &PORTx
    volatile uint16_t*  LAT;  //Pointer to &LATx
    uint16_t OUTPUT;          // The Dy port for PORTx.Dy
} OUTPUT;

extern OUTPUT output;

void init_output(OUTPUT output);
void output_SetDigitalOutput(OUTPUT output);
void output_SetLow(OUTPUT output);
void output_SetHigh(OUTPUT output);
void output_Toggle(OUTPUT output);

#endif /* OUTPUT_H_ */

