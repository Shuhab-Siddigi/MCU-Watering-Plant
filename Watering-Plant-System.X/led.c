#include "led.h"

void init_led(LED led)
{
    led_SetDigitalOutput(led);
}

void led_SetDigitalOutput(LED led)
{
    Set_PortBitState(led.TRIS, led.LED, OUTPUT);
    //*(led.TRIS) &= ~1UL << led.LED;
}

void led_SetLow(LED led)
{
    Set_PortBitState(led.LAT, led.LED, LOW);
    //*(led.LAT) &= ~1UL << led.LED;
}

void led_SetHigh(LED led)
{
    Set_PortBitState(led.LAT, led.LED, HIGH);
    //*(led.LAT) |= 1UL << led.LED;
}

void led_Toggle(LED led)
{
    Set_PortBitToggle(led.LAT, led.LED);
    //*(led.LAT) ^= 1UL << led.LED;
}