/*
 * File:   main.c
 * Author: shuhabsiddigi
 *
 * Created on April 8, 2021, 12:01 PM
 */





#include "configuration.h"

int main() {
    
       
 //   FLOATSWITCH_SetDigitalInput();
    init();

    while (1) {

        if (S1_GetValue() == 0) {
            LED1_SetHigh();
            LEDRED_SetHigh();
        } else {
            LED1_SetLow();
            LEDRED_SetLow();
        }
        
        if (S2_GetValue() == 0) {
            LED2_SetHigh();
        } else {
            LED2_SetLow();
        }
        
    }
    return 0;

}



