/*
 * File:   button.c
 * Author: shuhabsiddigi
 *
 * Created on April 13, 2021, 12:09 PM
 */


#include "button.h"

void init_input(INPUT input)
{
    input_SetDigitalInput(input);
}

void input_SetDigitalInput(INPUT input)
{
    Set_PortBitState(input.TRIS, input.BTN, INPUT);
    //*(input.PORT) |= (INPUT << input.PIN);
}

uint16_t input_GetValue(INPUT input)
{
    return read_PortBit(input.PORT, input.PIN);
    //return *(input.PORT) |= (input.PIN);
}