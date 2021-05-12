#ifndef _ADC_H
#define _ADC_H

/**
  Section: Included Files
*/
/*
  @Example
    <code>
        int conversion;
        ADC1_Initialize();
        ADC1_ChannelSelect(AN1_Channel);
        ADC1_Start();
        //Provide Delay
        for(int i=0;i <1000;i++)
        {
        }
        ADC1_Stop();
        while(!ADC1_IsConversionComplete())
        {
            ADC1_Tasks();   
        }
        conversion = ADC1_ConversionResultGet();
    </code>

*/


#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>


typedef enum 
{
    POT =  0xA,
    ADC1_CHANNEL_CTMU_TEMPERATURE_SENSOR_INPUT =  0xD,
    ADC1_CHANNEL_CTMU =  0xE,
    ADC1_CHANNEL_VBG_2 =  0x1B,
    ADC1_CHANNEL_VBG =  0x1C,
    ADC1_CHANNEL_AVSS =  0x1D,
    ADC1_CHANNEL_AVDD =  0x1E,
    ADC1_CHANNEL_VBAT_2 =  0x1F,
    ADC1_MAX_CHANNEL_COUNT = 8
} ADC1_CHANNEL;


//typedef enum{} ADC1_CHANNEL;
//struct ADC1_CHANNEL_TAG{CHANNEL ACD1_CHANNEL};


void init_adc (void);
void ADC_Start(void);
void ADC_Stop(void);
uint16_t ADC_ConversionResultBufferGet(uint16_t *buffer);
uint16_t ADC_ConversionResultGet(void);
bool ADC_IsConversionComplete( void );
void ADC_ChannelSelect( ADC1_CHANNEL channel );
uint16_t ADC_GetConversion(ADC1_CHANNEL channel);


#endif /*_ADC_H*/
    
