/*
 * File:   button.c
 * Author: shuhabsiddigi
 *
 * Created on April 13, 2021, 12:09 PM
 */


#include "button.h"

void btn_init(BTN btn)
{
    btn_SetDigitalInput(btn);
}

void btn_SetDigitalInput(BTN btn)
{
    Set_PortBitState(btn.TRIS, btn.BTN, INPUT);
    //*(btn.PORT) |= (INPUT << btn.BTN);
}

uint16_t btn_GetValue(BTN btn)
{
    return read_PortBit(btn.PORT, btn.BTN);
    //return *(btn.PORT) |= (btn.BTN);
}