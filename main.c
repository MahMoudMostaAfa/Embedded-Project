#include "tm4c123gh6pm.h"
#include "bit_utilies.h"
#include "GPS.h"
#include "UART.h"
#include "GPIO_SWITCHES.h"

int main (void) {

    RGBLED_Init();
    SW_Init();    
    //int param;
    while (1){
        unsigned char cond_sw1 = switch1_in();
        unsigned char cond_sw2 = switch2_in();
        if (cond_sw1 == 0x00 || cond_sw2 == 0x00){
            green_on();
        }
        // else if (Distance_chec(param)){
        //     green_on();
        // }
    }
}
