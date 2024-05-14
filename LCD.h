


// Prototypes
void LCD_Init(void);           //LCD initialization
void LCD_Cmd(char command);    //send commands to the LCD
void LCD_Data (char data );     //send data (1 byte) to the LCD
void LCD_Write_String(char String[]);   //prints a String to the LCD
void LCD_clear(void);  //clear screen


void LCD_Return_Home(void); // return cursor to its original site, and return display to its original status
void LCD_Function_Set(void); //to set bus mode,  number of lines display,   format display mode
void LCD_Cursor_ON(void); // show cursor
void LCD_Cursor_OFF(void); // hide cursor
void LCD_Cursor_Blink(void); // cursor is blinking (on-off-on-off....)
void Cursor_Shift_right(void); // shift cursor to the right
void Cursor_Shift_left(void); // shift cursor to the left
void Cursor_Movet_right(void); // cursor move after each write to the right
void Display_Shift_Right(void); // shift displayed data to the right
void Display_Shift_Left(void);  // shift displayed data to the left
void LCD_Set_Cursor(int line, int block); // set the position of the cursor