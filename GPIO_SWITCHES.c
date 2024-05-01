#include "tm4c123gh6pm.h"
#include "GPIO_SWITCHES.h"
#include <stdint.h>

#define SYSCTL_RCGCGPIO_R_VALUE 0x20
#define GPIO_PORTF_LOCK_R_VALUE GPIO_LOCK_KEY
#define ALL_LEDS_VALUE ALL_LEDS
#define ALL_SWITCHES_VALUE ALL_SWITCHES
#define GREEN_LED_VALUE GREEN_LED



//Initialize Port F LEDs
void RGBLED_Init(void){
    SYSCTL_RCGCGPIO_R |= SYSCTL_RCGCGPIO_R_VALUE;
    while((SYSCTL_PRGPIO_R & SYSCTL_RCGCGPIO_R_VALUE) == 0);
    GPIO_PORTF_LOCK_R = GPIO_PORTF_LOCK_R_VALUE;
    GPIO_PORTF_CR_R |= ALL_LEDS_VALUE;
    GPIO_PORTF_AMSEL_R &= ~ALL_LEDS_VALUE;
    GPIO_PORTF_AFSEL_R &= ~ALL_LEDS_VALUE;
    GPIO_PORTF_PCTL_R &= ~0x0000FFF0;
    GPIO_PORTF_DIR_R |= ALL_LEDS_VALUE;
    GPIO_PORTF_DEN_R |= ALL_LEDS_VALUE;
    GPIO_PORTF_DATA_R &= ~ALL_LEDS_VALUE;
}



//Initialize Port F Switches
void SW_Init(void){
    GPIO_PORTF_LOCK_R = GPIO_PORTF_LOCK_R_VALUE;
    GPIO_PORTF_CR_R |= ALL_SWITCHES_VALUE;
    GPIO_PORTF_AMSEL_R &= ~ALL_SWITCHES_VALUE;
    GPIO_PORTF_AFSEL_R &= ~ALL_SWITCHES_VALUE;
    GPIO_PORTF_PCTL_R &= ~0x000F000F;
    GPIO_PORTF_DIR_R &= ~ALL_SWITCHES_VALUE;
    GPIO_PORTF_DEN_R |= ALL_SWITCHES_VALUE;
    GPIO_PORTF_DATA_R &= ~ALL_SWITCHES_VALUE;
}


//take input from Switch 1 (PF0)
unsigned char switch1_in(void){
    return GPIO_PORTF_DATA_R & 0x01;
}


//turn on green led
void green_on (void){
    GPIO_PORTF_DATA_R |= GREEN_LED_VALUE;
}


//turn off green led
void green_off(void){
    GPIO_PORTF_DATA_R &= ~GREEN_LED_VALUE;                 
}


void Distance_check(int pass_100_meter){    /*value of *pass_100_meter* is 1 if distance exceeds 100 meters
																								0 if not                                                     */

	 /*turn on green led if the push button is pressed or 
		when the distance exceeds 100 meters*/  
    if (pass_100_meter || (switch1_in() != 0x01)) green_on();
    else green_off();
}
