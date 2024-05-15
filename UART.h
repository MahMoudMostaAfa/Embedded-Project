#ifndef UART_H
#define UART_H




void UART_0_Init(void);
char UART_0_Read(void);
void UART_0_Write(char data);
void UART_5_Init(void);
char UART_5_Read(void);
void UART_5_Write(char data);
void UART_5_Write_string(char* byte);
void UART_5_Read_string(char* str,int len);
void UART_0_Write_string(char* byte);
#endif
