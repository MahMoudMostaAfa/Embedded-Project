/*#include "tm4c123gh6pm.h"
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include "bit_utilies.h"
#include "GPS.h"
#include "UART.h"
#include "GPIO_SWITCHES.h"
#include "EEPROM.h"
#include "SysTick_Timer.h"
#include <stdlib.h>
#include <stdio.h>

*/
/*
int main (void) {

    int i=0;
    float totalDistance =0;
    char sTotalDistance[10];
    RGBLED_Init();
    SW_Init();
    UART_0_Init();
    UART_5_Init();
    SysTick_Init();
     bool initSuccess = EEPROM_Init(); 
    if (!initSuccess) {return 1;}
    //Test1 (EEPROM readall and writeall) //

    green_on();
    while (1){
        wait_ms(1000);
        float distance = GPS_main(&i);
        if (distance == -1){
            red_on();
        }else if (distance == 0) {
            blue_on();
        }else if (distance>0) {
            totalDistance += distance;
            green_on();
        }

        sprintf(sTotalDistance , "%f" ,totalDistance );
        UART_0_Write_string(sTotalDistance);
        

    }
}
*/

