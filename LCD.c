#include "tm4c123gh6pm.h"
#include "LCD.h"
#include "SysTick_Timer.h"
#include <stdint.h>
#include <string.h>



void systick_wait_1us(){
	NVIC_ST_CTRL_R=0;// CLEAR  ENABLE BIT
	NVIC_ST_RELOAD_R=16-1 ; //  (1us*SYS_CLK)-1
	NVIC_ST_CURRENT_R=0; //CLEAR CURRENT
	NVIC_ST_CTRL_R=0x05; // enable , inten ,clk_src ;
	while( (NVIC_ST_CTRL_R & 0x00010000) == 0) ; // make sure flag not set to 1

}


void wait_us(unsigned int time){
	unsigned int i;
	for(i=0;i<time;i++)
	{
		systick_wait_1us();
	}
}


//LCD initialization
//using pins A5==>RS    A6==>R/W   A7==>E  for control
//using pins B0=>B7 for Data
void LCD_Init(void) {
		//Port A pins 5,6,7  initialization
		SYSCTL_RCGCGPIO_R		  |=   0x03;
		while((SYSCTL_PRGPIO_R & 0x03)==0){};
		GPIO_PORTA_CR_R |=0xE0;
    GPIO_PORTA_DIR_R |= 0XE0;     //set PA5,6,7 as output
    GPIO_PORTA_DEN_R |= 0XE0;     //enable digital i/o on PA5,6,7
		GPIO_PORTB_CR_R |=0xFF;
		GPIO_PORTB_DIR_R  |= 0XFF;     //set PB0-7 as output
    GPIO_PORTB_DEN_R  |= 0XFF;     //enable digital I/O on PB0-7

		wait_ms(20);
			LCD_Cmd(Func_8bit_2line);
			wait_ms(5);
			LCD_Cmd(Func_8bit_2line);
			wait_us(100);
			LCD_Cmd(Func_8bit_2line);
			LCD_Cmd(Disp_off_cursor_off);
			LCD_Cmd(Clear_Disp);
			LCD_Cmd(Shift_cursor_right);
			LCD_Cmd(Disp_on_cursor_on);
}
//send commands to the LCD
void LCD_Cmd(unsigned int command) {
		GPIO_PORTA_DATA_R =0x00;  //clear A5==>RS    A6==>R/W   A7==>E
    GPIO_PORTB_DATA_R = command;  //set Pins B0=>7 as the passed command
		GPIO_PORTA_DATA_R = LCD_E;
		wait_us(1);
	  GPIO_PORTA_DATA_R = 0x00;
		wait_ms(2);

}

//send data (1 byte) to the LCD
void LCD_Data (unsigned char data ) {
        	GPIO_PORTA_DATA_R =LCD_RS;  //set A5==>RS  clear  A6==>R/W   A7==>E
		   //clear RS==>1    R/W==>0   E==>0
        	GPIO_PORTB_DATA_R = data;   //set Pins B0=>7 as the passed command
	GPIO_PORTA_DATA_R = LCD_E|LCD_RS;
	wait_us(1);
	  GPIO_PORTA_DATA_R=0;
		wait_ms(1);

}

//print a String to the LCD
void LCD_Write_String(char* String){
	int i=0;
	LCD_Cmd(Disp_on_cursor_off);

    while(String[i]!='\0'){
        LCD_Data(String[i]);
			i++;
}
}
