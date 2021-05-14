#include "output.h"

void init_output(OUTPUT output)
{
    output_SetDigitalOutput(output);
}

void output_SetDigitalOutput(OUTPUT output)
{
    Set_PortBitState(output.TRIS, output.OUTPUT, 0);
    //*(output.TRIS) &= ~1UL << output.PIN;
}

void output_SetLow(OUTPUT output)
{
    Set_PortBitState(output.LAT, output.OUTPUT, LOW);
    //*(output.LAT) &= ~1UL << output.PIN;
}

void output_SetHigh(OUTPUT output)
{
    Set_PortBitState(output.LAT, output.OUTPUT, HIGH);
    //*(output.LAT) |= 1UL << output.PIN;
}

void output_Toggle(OUTPUT output)
{
    Set_PortBitToggle(output.LAT, output.OUTPUT);
    //*(output.LAT) ^= 1UL << output.PIN;
}