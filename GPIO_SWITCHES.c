#include "tm4c123gh6pm.h"
#include "GPIO_SWITCHES.h"
#include <stdint.h>






//Initialize Port F LEDs
void RGBLED_Init(void){
    SYSCTL_RCGCGPIO_R |= 0x20;
    while((SYSCTL_PRGPIO_R & 0x20) == 0);
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
    GPIO_PORTF_PUR_R |= ALL_SWITCHES_VALUE;
    GPIO_PORTF_DEN_R |= ALL_SWITCHES_VALUE;
    //GPIO_PORTF_DATA_R &= ~ALL_SWITCHES_VALUE;
}
// Enablling switch interrupts
void enable_SW_Interrupts() {
    GPIO_PORTF_IS_R = ALL_SWITCHES_VALUE;
    GPIO_PORTF_IBE_R &= ~ALL_SWITCHES_VALUE;
    GPIO_PORTF_IEV_R &= ~ALL_SWITCHES_VALUE;
    GPIO_PORTF_IM_R |= ALL_SWITCHES_VALUE;
    // Enabling Interrupts of port F
    NVIC_PRI7_R |= 0x400000;
    NVIC_EN0_R |= 0x40000000;
}


//take input from Switch 1 (PF0)
unsigned char switch1_in(void){
    return GPIO_PORTF_DATA_R & 0x10;
}

unsigned char switch2_in(void){
    return GPIO_PORTF_DATA_R & 0x01;
}

void leds_off (){
    GPIO_PORTF_DATA_R &= ~ALL_LEDS_VALUE;
}

//turn on green led
void green_on (void){
    leds_off();
    GPIO_PORTF_DATA_R |= GREEN_LED_VALUE;
}

void blue_on (void){
    leds_off();
    GPIO_PORTF_DATA_R |= BLUE_LED;
}

void blue_off (void){
    GPIO_PORTF_DATA_R &= ~BLUE_LED;

}


//turn off green led
void green_off(void){

    GPIO_PORTF_DATA_R &= ~GREEN_LED_VALUE;                 
}

//turn on red led
void red_on (void){
    leds_off();
    GPIO_PORTF_DATA_R |= RED_LED;
}

//turn off red led
void red_off(void){
    GPIO_PORTF_DATA_R &= ~RED_LED;                 
}

void Distance_check(int pass_100_meter){    /*value of *pass_100_meter* is 1 if distance exceeds 100 meters
																								0 if not                                                     */

	 /*turn on green led if the push button is pressed or 
		when the distance exceeds 100 meters*/  
    if (pass_100_meter || (switch1_in() != 0x10)) green_on();
    else green_off();
}
