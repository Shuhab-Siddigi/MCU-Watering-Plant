#include "registerBits.h"

void Set_PortBitLow(volatile uint16_t* port, uint16_t bit)
{
    *(port) &= ~(1UL << bit);
}

void Set_PortBitHigh(volatile uint16_t* port, uint16_t bit)
{
    *(port) |= (1UL << bit);
}

void Set_PortBitToggle(volatile uint16_t* port, uint16_t bit)
{
    *(port) ^= (1UL << bit);
}

void Set_PortBitState(volatile uint16_t* port, uint16_t bit, uint16_t state)
{
    *(port) = (*(port) & ~(1UL << bit)) | (state << bit);
}

uint16_t Read_PortBit(volatile uint16_t* port, uint16_t bit)
{
    return !((*(port) >> bit) & 1UL);
}