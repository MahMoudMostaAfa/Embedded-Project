#include "tm4c123gh6pm.h"
#include "GPIO_SWITCHES.h"
#include <stdint.h>



//Initialize Port F lEDS


void RGBLED_Init(void){
SYSCTL_RCGCGPIO_R		  |=   0x20;
while((SYSCTL_PRGPIO_R & 0x20)==0);
GPIO_PORTF_LOCK_R 		 =   GPIO_LOCK_KEY;
GPIO_PORTF_CR_R 			|=   ALL_LEDS;
GPIO_PORTF_AMSEL_R 		&= ~ ALL_LEDS;
GPIO_PORTF_AFSEL_R	  &= ~ ALL_LEDS;
GPIO_PORTF_PCTL_R		  &= ~ 0x0000FFF0;
GPIO_PORTF_DIR_R		  |=   ALL_LEDS;
GPIO_PORTF_DEN_R		  |=   ALL_LEDS;
GPIO_PORTF_DATA_R 		&= ~ ALL_LEDS;
}


//Initialize Port F Switches

void SW_Init(void){
GPIO_PORTF_LOCK_R			=  GPIO_LOCK_KEY;
GPIO_PORTF_CR_R 		 |=  ALL_SWITCHES;
GPIO_PORTF_AMSEL_R 	 &=~ ALL_SWITCHES;
GPIO_PORTF_AFSEL_R   &=~ ALL_SWITCHES;
GPIO_PORTF_PCTL_R    &=~ 0x000F000F;
GPIO_PORTF_DIR_R     &=~ ALL_SWITCHES;
GPIO_PORTF_DEN_R     |=  ALL_SWITCHES;
GPIO_PORTF_DATA_R    &=~ ALL_SWITCHES;
}


//take input from Switch 1 (pf0)

unsigned char switch1_in(void){
return GPIO_PORTF_DATA_R & 0x01;
}


//turn on green led

void green_on (void){
GPIO_PORTF_DATA_R |= GREEN_LED;
}


//turn off green led

void green_off(void)
{
    GPIO_PORTF_DATA_R &=~ GREEN_LED;                 
}



void Distance_check(int pass_100_meter){      /*value of *pass_100_meter* is 1 if distance exceeds 100 meters
																								0 if not                                                     */

	 /*turn on green led if the push button is pressed or 
		when the distance exceeds 100 meters*/
	if   (pass_100_meter || (switch1_in()!=0x01)) green_on();
	
	else  green_off();
	
	
}
