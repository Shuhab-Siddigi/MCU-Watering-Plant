#include "output.h"

void init_output(OUTPUT output)
{
    output_SetDigitalOutput(output);
}

void output_SetDigitalOutput(OUTPUT output)
{
    Set_PortBitState(output.TRIS, output.PIN, OUTPUT);
    //*(output.TRIS) &= ~1UL << output.PIN;
}

void output_SetLow(OUTPUT output)
{
    Set_PortBitState(output.LAT, output.PIN, LOW);
    //*(output.LAT) &= ~1UL << output.PIN;
}

void output_SetHigh(OUTPUT output)
{
    Set_PortBitState(output.LAT, output.PIN, HIGH);
    //*(output.LAT) |= 1UL << output.PIN;
}

void output_Toggle(OUTPUT output)
{
    Set_PortBitToggle(output.LAT, output.PIN);
    //*(output.LAT) ^= 1UL << output.PIN;
}