
#include "mcc_generated_files/system.h"

/*
                         Main application
 */

#include "mcc_generated_files/mcc.h"

uint8_t i;

int main(void)
{
   
    SYSTEM_Initialize();
  
    int conversion;
 //   ADC1_ChannelSelect(POT);

    while(1){

        
        conversion = ADC1_GetConversion(POT);

        if(conversion <= 300){
            RED_SetHigh();
            GREEN_SetLow();
            BLUE_SetLow();
        }else if ( conversion > 300 && conversion <= 600){
            RED_SetLow();
            GREEN_SetHigh();
            BLUE_SetLow();
        }else{
            RED_SetLow();
            GREEN_SetLow();
            BLUE_SetHigh();
        }
    }
    
}

