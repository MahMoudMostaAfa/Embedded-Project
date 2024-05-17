#include "tm4c123gh6pm.h"
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include "bit_utilies.h"
#include "GPS.h"
#include "UART.h"
#include "GPIO_SWITCHES.h"
#include "EEPROM.h"
#include <stdlib.h>
#include <stdio.h>
#include "SysTick_Timer.h"

int flag = 0;
int i=0; // counter
void GPIOF_Handler() {
	uint32_t interrupt_status = GPIO_PORTF_MIS_R;
	if(interrupt_status & 0x10) {
		GPIO_PORTF_ICR_R |= 0x10;
		flag = 1;
	}
    else if ((interrupt_status & 0x1) && flag) {
        int j;
        char* finalOutput;
        int finalLength =strlen(finalOutput);
        finalOutput = GPS_getOutput(i);
        while (UART_0_Read() != 'D') ;
        for (j = 0; j < finalLength; j++) UART_0_Write(*finalOutput++);
        GPIO_PORTF_ICR_R |= 1;
    }
}


int main (void) {
	float totalDistance =0;
	char sTotalDistance[10];
	bool initSuccess;
	float distance;
	RGBLED_Init();
    SW_Init();
	enable_SW_Interrupts();
    UART_0_Init();
    UART_5_Init();
    SysTick_Init();
    initSuccess = EEPROM_Init();
    if (!initSuccess) {return 1;} 
    while (1){
        if(flag) {
            while(1);
        }
        else {
            wait_sec(2);
            distance = GPS_main(&i);
            if (distance == -1){
                red_on();
                wait_ms(500);
                //red_off();
            }else if (distance == 0) {
                blue_on();
                wait_ms(500);
                //blue_off();
            }else if (distance>0) {
                totalDistance += distance;
                green_on();
                wait_ms(500);
                //green_off();
            }
            sprintf(sTotalDistance , "%f" ,totalDistance);
            UART_0_Write_string(sTotalDistance);
        }
    }
}
