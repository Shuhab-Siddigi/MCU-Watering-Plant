#ifndef FLOATSWITCH_H_
#define	FLOATSWITCH_H_


#include "constants.h"

#define FLOATSWITCH_SetDigitalInput()(_TRISA8 = DIGITAL)

#define FLOATSWITCH_GetValue()  _RA8

void init_floatswitch();

#endif	/* FLOATSWITCH_H_ */

