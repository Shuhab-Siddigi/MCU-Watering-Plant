/*
 * File:   button.c
 * Author: shuhabsiddigi
 *
 * Created on April 13, 2021, 12:09 PM
 */


#include "input.h"

void init_input(INPUT input)
{
    input_SetDigitalInput(input);
}

void input_SetDigitalInput(INPUT input)
{
    Set_PortBitState(input.TRIS, input.INPUT, 1);
    //*(input.PORT) |= (INPUT << input.PIN);
}

uint16_t input_GetValue(INPUT input)
{
    return Read_PortBit(input.PORT, input.INPUT);
    //return *(input.PORT) |= (input.PIN);
}