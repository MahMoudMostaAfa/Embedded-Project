#include "UART.h"
#include "tm4c123gh6pm.h"

// initialze UART 0
void UART_0_Init(void){
	SYSCTL_RCGCUART_R|=0x0001;//active uart0
	SYSCTL_RCGCGPIO_R|=0x0001; ;// active port A 
	
	UART0_CTL_R=0 ; //disble uart
	UART0_IBRD_R = 104 ; // int( 16M /16*9600) 
	UART0_FBRD_R=11 ;  // int(.16*64 +.5)
	UART0_LCRH_R= 0x0070 ;// 8-bit word length ,enable fifo
	UART0_CTL_R =0x0301; //enable uart
	GPIO_PORTA_AFSEL_R|=0x03; //enable alt function PA0,PA1
	GPIO_PORTA_PCTL_R |=  0x00000011; // configure uart for PA0 ,PA1
	GPIO_PORTA_DEN_R |=0x03;// enable digital
	GPIO_PORTA_AMSEL_R%=~0x03; //disble analog
	
}
// read data for UART 0
char UART_0_Read(void){
	while( (UART0_FR_R & 0x0010)!=0); // stuck when fifo is empty
	return (char) (UART0_DR_R & 0xFF);
}
// Write data for UART 0
void UART_0_Write(char data){
	while((UART0_FR_R & 0x0020) != 0); // check if fifo is full
	UART0_DR_R = data;
}



// initialze UART 1
void UART_5_Init(void){
	SYSCTL_RCGCUART_R|=0x0020;//active uart5
	SYSCTL_RCGCGPIO_R|=0x0010; ;// active port E 
	
	UART5_CTL_R=0 ; //disble uart
	UART5_IBRD_R = 104 ; // int( 16M /16*9600) 
	UART5_FBRD_R=11 ;  // int(.16*64 +.5)
	UART5_LCRH_R= 0x0070 ;// 8-bit word length ,enable fifo
	UART5_CTL_R =0x0301; //enable uart
	GPIO_PORTE_AFSEL_R|=0x30; //enable alt function PA0,PA1
	GPIO_PORTE_PCTL_R |=  0x00011000; // configure uart for PE4 ,PE5
	GPIO_PORTE_DEN_R |=0x30;// enable digital
	GPIO_PORTE_AMSEL_R%=~0x30; //disble analog
	
}
// Write data for UART 1
void UART_5_Write(char data) {
	while ((UART5_FR_R & 0x0020)!=0) ; 	// check if fifo is full
	UART5_DR_R = data ;
}
// read data for UART 1
char UART_5_Read(void){
	while ((UART5_FR_R & 0x0010)!=0);	// check if fifo is empty
	return (char) (UART5_DR_R & 0xFF);
}
void UART_5_Read_string(char* str,int len){
	char c;
	for(int i=0;i<len;i++){
		c=UART_5_Read();
		if (c!=0x0D){
			str[i]=c;
	}else {
		str[i]='\0';
		break;
}
	}
}
void UART_5_Write_string(char* byte){
	while (*byte){
		UART_5_Write(*byte);
		byte++;
	}
}
