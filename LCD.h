#ifndef LCD_H
#define LCD_H
//Macros
#define LCD_RS 0x20 											//RS pin
#define LCD_E 0x80 												//E pin
#define Func_8bit_2line 0x38							//8 bits,  2 lines display,   5 x 7 matrix
#define Disp_off_cursor_off 0x08					// display off and cursor off
#define Disp_on_cursor_on 0x0E						// display on and cursor on
#define Disp_on_cursor_off 0x0C						// display on and hide cursor
#define Shift_cursor_right 0x06						// shift cursor to the right
#define Clear_Disp 0x01										//clear screen

// Prototypes
void LCD_Init(void);           					 //LCD initialization
void LCD_Cmd(unsigned int command);      //send commands to the LCD
void LCD_Data (unsigned char data );     //send data (1 byte) to the LCD
void LCD_Write_String(char String[]);    //prints a String to the LCD
 

/*
void LCD_Return_Home(void); // return cursor to its original site, and return display to its original status
void LCD_Function_Set(void); //to set bus mode,  number of lines display,   format display mode
void LCD_Cursor_ON(void); // show cursor
void LCD_Cursor_OFF(void); // hide cursor
void LCD_Cursor_Blink(void); // cursor is blinking (on-off-on-off....)
void Cursor_Shift_right(void); 
void Cursor_Shift_left(void); // shift cursor to the left
void Cursor_Movet_right(void); // cursor move after each write to the right
void Display_Shift_Right(void); // shift displayed data to the right
void Display_Shift_Left(void);  // shift displayed data to the left
void LCD_Set_Cursor(int line, int block); // set the position of the cursor
void LCD_clear(void); 
*/
#endif /*LCD_H*/
