#include "UART.h"
#include "tm4c123gh6pm.h"
#include "bit_utilies.h"
// initialze UART 0
void UART_0_Init(void){
	SET(SYSCTL_RCGCUART_R,SYSCTL_RCGCUART_R0);//active uart0
	SET(SYSCTL_RCGCGPIO_R,SYSCTL_RCGCUART_R0) ;// active port A 
	while((SYSCTL_PRGPIO_R & SYSCTL_RCGCUART_R0)==0); //DELAY
	CLR(UART0_CTL_R ,UART_CTL_UARTEN) ; //disble uart
	UART0_IBRD_R = 104 ; // int( 16M /16*9600) 
	UART0_FBRD_R=11 ;  // int(.16*64 +.5)
	UART0_LCRH_R= 0x0070 ;// 8-bit word length ,enable fifo
	SET(GPIO_PORTA_AFSEL_R,0x03); //enable alt function PA0,PA1
	GPIO_PORTA_PCTL_R = (GPIO_PORTA_PCTL_R & 0xFFFFFF00) + 0x00000011; // configure uart for PA0 ,PA1
	SET(GPIO_PORTA_DEN_R ,0x03);// enable digital
	CLR_BIT(GPIO_PORTA_AMSEL_R,0x03); //disble analog
	
}
// read data for UART 0
char UART_0_Read(void){
	while( (UART0_FR_R & 0x0010)!= 0 ) ; // check if fifo is empty
	return (char) (UART0_DR_R & 0xFF);
}
// Write data for UART 0
void UART_0_Write(char data){
	while((UART0_FR_R & 0x0020) != 0); // check if fifo is full
	UART0_DR_R = data;
}



// initialze UART 1
void UART_1_Init(void){
	SET(SYSCTL_RCGCUART_R,SYSCTL_RCGCUART_R1);//active uart1
	SET(SYSCTL_RCGCGPIO_R,SYSCTL_RCGCUART_R1) ;// active port B 
	while((SYSCTL_PRGPIO_R & SYSCTL_RCGCUART_R1)==0); //DELAY
	CLR(UART1_CTL_R ,UART_CTL_UARTEN) ; //disble uart
	UART1_IBRD_R = 104 ; // int( 16M /16*9600) 
	UART1_FBRD_R=11 ;  // int(.16*64 +.5)
	UART1_LCRH_R= 0x0070 ;// 8-bit word length ,enable fifo
	SET(GPIO_PORTB_AFSEL_R,0x03); //enable alt function PB0,PB1
	GPIO_PORTB_PCTL_R = (GPIO_PORTA_PCTL_R & 0xFFFFFF00) + 0x00000011; // configure uart for PA0 ,PA1
	SET(GPIO_PORTB_DEN_R ,0x03);// enable digital
	CLR_BIT(GPIO_PORTB_AMSEL_R,0x03); //disble analog
	
}
// read data for UART 1
char UART_1_Read(void){
	while( (UART1_FR_R & 0x0010)!= 0 ) ; // check if fifo is empty
	return (char) (UART1_DR_R & 0xFF);
}
// Write data for UART 1
void UART_1_Write(char data){
	while((UART1_FR_R & 0x0020) != 0); // check if fifo is full
	UART1_DR_R = data;
}


int main(){}
