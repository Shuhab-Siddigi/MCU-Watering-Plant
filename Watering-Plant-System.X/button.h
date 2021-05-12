#ifndef BUTTON_H_
#define BUTTON_H_


#include "registerBits.h"


typedef struct
{
    volatile uint16_t*  TRIS; //Pointer to &TRISx
    volatile uint16_t*  PORT; //Pointer to &PORTx
    uint16_t BTN;               // The Dy port for PORTx.Dy
} BTN;

extern BTN btn;

void init_btn(BTN btn);
void btn_SetDigitalInput(BTN btn);
uint16_t btn_GetValue(BTN btn);

#endif	/* BUTTON_H_ */

