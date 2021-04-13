#include <xc.h>
#include "adc.h"
typedef struct
{
	uint8_t intSample;
}

ADC_OBJECT;

static ADC_OBJECT adc_obj;

void init_adc (void)
{
    // ASAM enabled; DMABM disabled; ADSIDL disabled; DONE disabled; DMAEN disabled; FORM Absolute decimal result, unsigned, right-justified; SAMP disabled; SSRC Internal counter ends sampling and starts conversion; MODE12 10-bit; ADON enabled; 

   AD1CON1 = 0x8074;

    // CSCNA disabled; NVCFG0 AVSS; PVCFG AVDD; ALTS disabled; BUFM disabled; SMPI Generates interrupt after completion of every sample/conversion operation; OFFCAL disabled; BUFREGEN disabled; 

   AD1CON2 = 0x0000;

    // SAMC 31; EXTSAM disabled; PUMPEN disabled; ADRC RC clock; ADCS 0; 

   AD1CON3 = 0x9F00;

    // CH0SA AN0; CH0SB AN0; CH0NB AVSS; CH0NA AVSS; 

   AD1CHS = 0x0000;

    // CSS31 disabled; CSS30 disabled; CSS29 disabled; CSS28 disabled; CSS27 disabled; 

   AD1CSSH = 0x0000;

    // CSS9 disabled; CSS8 disabled; CSS7 disabled; CSS6 disabled; CSS5 disabled; CSS4 disabled; CSS3 disabled; CSS2 disabled; CSS1 disabled; CSS14 disabled; CSS0 disabled; CSS13 disabled; CSS12 disabled; CSS11 disabled; CSS10 disabled; 

   AD1CSSL = 0x0000;

    // VBG2EN disabled; VBGEN disabled; 

   ANCFG = 0x0000;


   adc_obj.intSample = AD1CON2bits.SMPI;
   
   // Enabling ADC1 interrupt.
   IEC0bits.AD1IE = 1;
}

void ADC_Start()
{
   AD1CON1bits.SAMP = 1;
}
void ADC_Stop()
{
   AD1CON1bits.SAMP = 0;
}
uint16_t ADC_ConversionResultBufferGet(uint16_t *buffer)
{
    int count;
    uint16_t *ADC16Ptr;

    ADC16Ptr = (uint16_t *)&(ADC1BUF0);

    for(count=0;count<=adc_obj.intSample;count++)
    {
        buffer[count] = (uint16_t)*ADC16Ptr;
        ADC16Ptr++;
    }
    return count;
}
uint16_t ADC_ConversionResultGet()
{
    return ADC1BUF0;
}
bool ADC_IsConversionComplete()
{
    return AD1CON1bits.DONE; //Wait for conversion to complete   
}
void ADC_ChannelSelect( ADC1_CHANNEL channel )
{
    AD1CHS = channel;
}

uint16_t ADC_GetConversion(ADC1_CHANNEL channel)
{
    ADC_ChannelSelect(channel);
    
    ADC_Start();
    ADC_Stop();
    
    while (!ADC_IsConversionComplete()){}
       
    return ADC_ConversionResultGet();
}


void __attribute__ ( ( __interrupt__ , auto_psv ) ) _ADC1Interrupt ()
{
    // clear the ADC interrupt flag
    IFS0bits.AD1IF = false;
}


/**
  End of File
*/
