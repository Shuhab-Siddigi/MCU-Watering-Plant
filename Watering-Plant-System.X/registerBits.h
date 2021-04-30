#ifndef REGISTERBITS_H_
#define REGISTERBITS_H_

#include "configuration.h"


void Set_PortBitHigh(volatile uint16_t* port, uint16_t bit);
void Set_PortBitLow(volatile uint16_t* port, uint16_t bit);
void Set_PortBitToggle(volatile uint16_t* port, uint16_t bit);
void Set_PortBitState(volatile uint16_t* port, uint16_t bit, uint16_t state);
uint16_t read_PortBit(volatile uint16_t* port, uint16_t bit);


#endif /* REGISTERBITS_H_ */