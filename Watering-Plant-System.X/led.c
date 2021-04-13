#include "led.h"

void init_led()
{
    LED1_SetDigitalOutput();
    LED2_SetDigitalOutput();
    LEDRED_SetDigitalOutput();

}