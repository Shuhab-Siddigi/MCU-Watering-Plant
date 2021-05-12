#ifndef CONFIGURATION_H_
#define CONFIGURATION_H_



// USED IN libpic30 
#define SYS_FREQ 4000000UL //Clock Frequency
#define FCY (SYS_FREQ/2) //Cycle Frequency
// This library is used for delay functions

#include <libpic30.h>


//#include "floatswitch.h"
//#include "led.h"
//#include "button.h"
#include "constants.h"
//#include "adc.h"

void init();

#endif	/*CONFIGURATION_H_ */
