
#include "mcc_generated_files/system.h"
#include "mcc_generated_files/pin_manager.h"
#include "mcc_generated_files/system.h"

 #include <stdio.h>
 #include <stdlib.h>

#define SYS_FREQ 8000000UL //Clock Frequency
#define FCY (SYS_FREQ/2) //Cycle Frequency

// This library is used for delay functions
#include <libpic30.h>
#include "adc.h"

//	0x01	Clear Display (also clear DDRAM content)
// 	0x02	Return home
//  0x03    Clear screen
//	0x04	Decrement cursor (shift cursor to left)
//	0x06	Increment cursor (shift cursor to right)
//	0x05	Shift display right
//	0x07	Shift display left
//	0x08	Display off, cursor off
//	0x0A	Display off, cursor on
//	0x0C	Display on, cursor off
//	0x0E	Display on, cursor blinking
//	0x0F	Display on, cursor blinking
//	0x10	Shift cursor position to left
//	0x14	Shift cursor position to right
//	0x18	Shift the entire display to the left
//	0x1C	Shift the entire display to the right
//	0x80	Force cursor to beginning ( 1st line)
//	0xC0	Force cursor to beginning ( 2nd line)
//  0x28    4-bit mode 
//  0x38	8-bit mode

/*
 * Define these pins 
 RS
 Enable 
 D4
 D5
 D6
 D7
 */

//Based on the Hex value Set the Bits of the Data Lines
void LCD_SetBit(char hex){ 
    if (hex & 1) D4_SetHigh(); else D4_SetLow();
    if (hex & 2) D5_SetHigh(); else D5_SetLow();
    if (hex & 4) D6_SetHigh(); else D6_SetLow();
    if (hex & 8) D7_SetHigh(); else D7_SetLow(); 
}

void LCD_Instruction(char hex){
    RS_SetLow();            
    LCD_SetBit(hex); //Incoming Hex value
    Enable_SetHigh(); __delay_ms(4); Enable_SetLow();
    LCD_SetBit(0x00); //Reset all pins to 0
    __delay_ms(4);
}

void init_LCD(){
  LCD_SetBit(0x00);        // <- set all pins low 
  LCD_Instruction(0x03);   
  __delay_ms(20);
  LCD_Instruction(0x03);    
   __delay_ms(20);
  LCD_Instruction(0x03);    // <- Set to 4 - bit instead of 8-bit 
  __delay_ms(20);
  LCD_Instruction(0x02);    // <- 00000011
  LCD_Instruction(0x02);    // <- Return home -> Clears the RAM and initializes the LCD
  __delay_ms(20);
  LCD_Instruction(0x08);    // <- Select Row 1
  LCD_Instruction(0x00);    // <- Clear Row 1 Display
  __delay_ms(20);
  LCD_Instruction(0x0C);    // <- Select Row 2
  LCD_Instruction(0x00);    // <- Clear Row 2 Display  
  __delay_ms(20);
  LCD_Instruction(0x06);    // <- Entry instruction -> (0, 1 ,Increment DDRAM counter,Shift screen)
   __delay_ms(20);
}


void LCD_ClearScreen() {
    LCD_Instruction(0); // <- Clear the LCD
    LCD_Instruction(1); // <- Move the cursor to first position
}

void LCD_Data(char hex){
    RS_SetHigh();           
    LCD_SetBit(hex); // <- Incoming Hex value
    Enable_SetHigh();         
    __delay_ms(1);
    Enable_SetLow();
    LCD_SetBit(0x00); // <- Reset all pins to 0
    RS_SetLow();     
}

void LCD_Set_Cursor(char column, char row){
    char temp,x,y;
    if(column == 1) {
      temp = 0x80 + row - 1;    // <- 80H is used to move the cursor
        x = temp>>4;            // <- Lower 8-bits
        y = temp & 0x0F;        // <- Upper 8-bits
        LCD_Instruction(x);     // <- Set Row
        LCD_Instruction(y);     // <- Set Column
    }
    else if(column == 2)
    {
        temp = 0xC0 + row - 1;
        x = temp>>4;            // <- Lower 8-bits
        y = temp & 0x0F;        // <- Upper 8-bits
        LCD_Instruction(x);     // <- Set Row
        LCD_Instruction(y);     // <- Set Column
    }
}

 //Send 8-bits through 4-bit mode
void LCD_Print_Char(char data,int speed) 
{
   char Lower_Nibble,Upper_Nibble;
   Lower_Nibble = data&0x0F;
   Upper_Nibble = data&0xF0;
   RS_SetHigh();            
   
   LCD_SetBit(Upper_Nibble>>4); // <- Send upper half by shifting by 4
   Enable_SetHigh();
   __delay_ms(speed);
   Enable_SetLow();
   
   LCD_SetBit(Lower_Nibble); // <- Send Lower half
   Enable_SetHigh();
   __delay_ms(speed);
   Enable_SetLow();
   
}

void LCD_Print_String(char *str, int speed){
    
    int i = 0;
    //Split the string using pointers and call the Char function 
    while(str[i]!= '\0'){
        LCD_Print_Char(str[i],speed);
        i++;
    }
    
}


void LCD_intro(){
    
    LCD_ClearScreen();
    LCD_Set_Cursor(1,1);
    LCD_Print_String("    Welcome! ",50);
    __delay_ms(100);
    LCD_ClearScreen();
    LCD_Set_Cursor(1,1);
    LCD_Print_String("  Water Plant  ",50);
    LCD_Set_Cursor(2,1);
    LCD_Print_String("     System    ",50);
    __delay_ms(100);
    LCD_ClearScreen();
    LCD_Set_Cursor(1,1);
    LCD_Print_String("Moisture % = ",0);
    LCD_Set_Cursor(2,1);
    LCD_Print_String("Moisture V = ",0);
    
}


int main() {
    
    SYSTEM_Initialize();
    init_LCD();
    LCD_intro();
    init_ADC();
    
    char str[100];
    double value;
    double size = 1024;
    double percent = 100;
    double result;
    
     while (1) {    
         
         value = ADC_GetConversion(WATERSENSOR);
         result = (value / size)*percent;
         sprintf(str, "%.0f", result);
         
         LCD_Set_Cursor(1,14);
         LCD_Print_String(str,0);
         
        

        
        
        
    }
   
    return 0;
}