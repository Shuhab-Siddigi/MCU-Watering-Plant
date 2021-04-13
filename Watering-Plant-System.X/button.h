#ifndef BUTTON_H_
#define BUTTON_H_


#include "constants.h"

#define S1_SetDigitalInput()(_TRISC9 = INPUT)
#define S1_GetValue()         _RC9

#define S2_SetDigitalInput()(_TRISC8 = INPUT)
#define S2_GetValue()         _RC8


void init_button();

#endif	/* BUTTON_H_ */

