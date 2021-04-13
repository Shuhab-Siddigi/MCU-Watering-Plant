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
    
    int conversion;
    
    while (1) {

        conversion = ADC_GetConversion(POT);

        if(S1_GetValue() == 0){
            LED1_SetHigh();

           
            LEDRED_SetLow();
            LEDGREEN_SetLow();
            LEDBLUE_SetLow();
        }else if(conversion <= 300){
            LED1_SetLow();

     
            LEDRED_SetLow();
            LEDBLUE_SetLow();
            
            LEDGREEN_SetHigh();
        }else if ( conversion > 300 && conversion <= 600){
            LED1_SetLow();

     
            LEDRED_SetLow();
            LEDGREEN_SetLow();
           
            LEDBLUE_SetHigh();
   
        }else{
            LED1_SetLow();
            
            LEDBLUE_SetLow();
            LEDGREEN_SetLow();
   
            LEDRED_SetHigh();
        }
    
        
    }
    return 0;

}



