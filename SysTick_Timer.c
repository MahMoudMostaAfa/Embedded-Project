#include "tm4c123gh6pm.h"
#include <stdint.h>
#include "SysTick_Timer.h"
void SysTick_Init() // To initialize SysTick Counter
{
	NVIC_ST_CTRL_R = 0;    //disable SysTick during setup
	NVIC_ST_RELOAD_R = 0X00FFFFFF;  // just intial val for the RELOAD register
	NVIC_ST_CURRENT_R = 0; // to assure that any Curren val clear
	NVIC_ST_CTRL_R = 0X05; // Enable the SysTick with no intrrupt
}

void systick_wait_1ms(){
	NVIC_ST_CTRL_R=0;// CLEAR  ENABLE BIT
	NVIC_ST_RELOAD_R=16000-1 ; //  (1ms*SYS_CLK)-1
	NVIC_ST_CURRENT_R=0; //CLEAR CURRENT
	NVIC_ST_CTRL_R=0x05; // enable , inten ,clk_src ;
	while( (NVIC_ST_CTRL_R & 0x00010000) == 0) ; // make sure flag not set to 1 
	
}

void wait_ms(unsigned int time){
	unsigned int i;
	for(i=0 ;i<time ; i++ ){
		systick_wait_1ms();
	}
}
void wait_sec(unsigned int seconds) {
    NVIC_ST_CTRL_R = 0;					// disable the SysTick Timer
    NVIC_ST_CURRENT_R = 0; 			    // resets the countflag
    NVIC_ST_RELOAD_R = 16000000 - 1;    // count for 1 second at a time
    NVIC_ST_CTRL_R |= 0x5; 			    // enable the timer with interrupt disabled
    while(seconds > 0){
        while ((NVIC_ST_CTRL_R & 0x10000) == 0); // Check for countflag
        seconds--;
    }
    NVIC_ST_RELOAD_R = 0; // To avoid counting after the function is complete
    NVIC_ST_CTRL_R = 0;
}