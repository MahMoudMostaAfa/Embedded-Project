


// Prototypes
void LCD_Init(void);           //LCD initialization
void LCD_Cmd(char command);    //send commands to the LCD
void LCD_Data (char data );     //send data (1 byte) to the LCD
void LCD_Write_String(char String[]);   //prints a String to the LCD
void LCD_clear(void);            //clear screen