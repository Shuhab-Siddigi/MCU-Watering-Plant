#ifndef INPUT_H_
#define INPUT_H_


#include "registerBits.h"


typedef struct
{
    volatile uint16_t*  TRIS; //Pointer to &TRISx
    volatile uint16_t*  PORT; //Pointer to &PORTx
    uint16_t INPUT;               // The Dy port for PORTx.Dy
} INPUT;

extern INPUT input;

void init_input(INPUT input);
void input_SetDigitalInput(INPUT input);
uint16_t input_GetValue(INPUT input);

#endif	/* INPUT_H_ */

