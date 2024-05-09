#include "tm4c123gh6pm.h"
#include "LCD.h"
#include "SysTick_Timer.h"
#include <stdint.h>
#include <string.h>

#define LCD_RS 0x20 //RS pin
#define LCD_E 0x80  //E pin

//LCD initialization
//using pins A5==>RS    A6==>R/W   A7==>E  for control
//using pins B0=>B7 for Data
void LCD_Init(void) {
		//Port A pins 5,6,7  initialization
		SYSCTL_RCGCGPIO_R		  |=   0x01;
		while((SYSCTL_PRGPIO_R & 0x01)==0){};

    GPIO_PORTA_AFSEL_R &= ~0xE0;    //disable alternative functions for PA5,6,7
    GPIO_PORTA_AMSEL_R &= ~0XE0;    
    GPIO_PORTA_PCTL_R &= ~0xFFF00000;;     
    GPIO_PORTA_DIR_R |= 0XE0;     //set PA5,6,7 as output 
    GPIO_PORTA_DEN_R |= 0XE0;     //enable digital i/o on PA5,6,7
	
//Port B  initialization
	
		SYSCTL_RCGCGPIO_R |=   0x02;
		while((SYSCTL_PRGPIO_R & 0x02)==0){};
    GPIO_PORTB_AFSEL_R &= ~0xff;   //disable alt functions for PB0-7
    GPIO_PORTB_AMSEL_R &= ~0Xff;   //disable analog functions for PB0-7
    GPIO_PORTB_PCTL_R &= ~0XFF;     
    GPIO_PORTB_DIR_R  |= 0XFF;     //set PB0-7 as output
    GPIO_PORTB_DEN_R  |= 0XFF;     //enable digital I/O on PB0-7
	  	
}
//send commands to the LCD
void LCD_Cmd(char command) {
		GPIO_PORTA_DATA_R &=~0xE0;  //clear A5==>RS    A6==>R/W   A7==>E
	
    		GPIO_PORTB_DATA_R = command;  //set Pins B0=>7 as the passed command 
	
		GPIO_PORTA_DATA_R |= LCD_E;  
		wait_ms(3);
		GPIO_PORTA_DATA_R &=~0xE0;  //clear A5==>RS    A6==>R/W   A7==>E
   						 
}

//send data (1 byte) to the LCD
void LCD_Data (char data ) {
        	GPIO_PORTA_DATA_R &=~0xE0;  //clear A5==>RS    A6==>R/W   A7==>E
		GPIO_PORTA_DATA_R |= LCD_RS;   //clear RS==>1    R/W==>0   E==>0
        	GPIO_PORTB_DATA_R = data;   //set Pins B0=>7 as the passed command 
	
		GPIO_PORTA_DATA_R |= LCD_E;   
		wait_ms(3);
		GPIO_PORTA_DATA_R &=~0xE0;   //clear A5==>RS    A6==>R/W   A7==>E
}

//print a String to the LCD
void LCD_Write_String(char String[]){
    for(int i=0;i<strlen(String);i++)
        LCD_Data(String[i]);
}

//clear screen
void LCD_clear(void){
    LCD_Cmd(0x01);
}


//set 8-bit bus mode,   set 2 lines display mode,   set 5*8 dot format display mode
void LCD_Function_Set(void)
{
	LCD_Cmd(0x38);
}


// return cursor to its original site, and return display to its original status
void LCD_Return_Home(void)
{
	LCD_Cmd(0x02);
}


// Turn ON cursor
void LCD_Cursor_ON(void)
{
	LCD_Cmd(0x0E);
}

// Turn OFF cursor
void LCD_Cursor_OFF(void)
{
	LCD_Cmd(0x0C);
}

// make cursor blink (on-off-on-off...)
void LCD_Cursor_Blink(void)
{
	LCD_Cmd(0x0F);
}

// shift displayed data to the right, cursor follows the shift
void Display_Shift_Right(void)
{
	LCD_Cmd(0x1C);
}

// shift displayed data to the left, cursor follows the shift
void Display_Shift_Left(void)
{
	LCD_Cmd(0x18);
}

// shift cursor to the right 
void Cursor_Shift_right(void)
{
	LCD_Cmd(0x14);
}

// shift cursor to the left 
void Cursor_Shift_left(void)
{
	LCD_Cmd(0x10);
}

// set the position of the cursor, choose line (1 or 2), choose block (0 to 15)
void LCD_Set_Cursor(int line, int block) {
  if (line == 1 & block <= 15) {
    LCD_Cmd(0X80 + block);
  }
  else if (line == 2 & block <= 15) {
    LCD_Cmd(0xC0 + block);
  }
  else {
    LCD_Cmd(0x80);
  }
}
