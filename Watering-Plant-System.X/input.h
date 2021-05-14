#ifndef BUTTON_H_
#define BUTTON_H_


#include "registerBits.h"


typedef struct
{
    volatile uint16_t*  TRIS; //Pointer to &TRISx
    volatile uint16_t*  PORT; //Pointer to &PORTx
    uint16_t PIN;               // The Dy port for PORTx.Dy
} INPUT;

extern INPUT input;

void init_btn(INPUT input);
void btn_SetDigitalInput(INPUT input);
uint16_t btn_GetValue(INPUT input);

#endif	/* BUTTON_H_ */

