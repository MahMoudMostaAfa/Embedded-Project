#include "tm4c123gh6pm.h"
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include "bit_utilies.h"
//#include "GPS.h"
#include "UART.h"
#include "GPIO_SWITCHES.h"
#include "EEPROM.h"

int main (void) {
    RGBLED_Init();
    SW_Init();
    UART_0_Init();
		bool initSuccess = EEPROM_Init();
    if (!initSuccess) {return 1;} 
    // Test1 (EEPROM readall and writeall) //

    char test1[18] = "Hi, this is a test";   
    EEPROM_writeall(test1, 18);
    char test2[18];
    EEPROM_readall(&test2);
    bool flag = true;
    for (char i = 0; i < 18; i++) {
        if (test1[i] != test2[i]) {
            flag = false;
            break;
        }
    }
    if (flag) green_on();
    else red_on();
    while (1);

    //int param;

    //* Test2 (UART to PC and interfacing Python script) *//

//    char test1[] = "30.06644068281403,31.279806995999685|31.0216594,33";
//    while (1) {
//        char protocol = UART_0_Read();
//        if (protocol == 'S') {
//            UART_0_Write(51);
//            break;
//        }
//    }
//    while (1) {
//        char protocol = UART_0_Read();
//        if (protocol == 'D') break;
//    }
//    for (char i = 0; i < 51 ; i++) {
//        UART_0_Write(test1[i]);
//    }
//    green_on();
//    while (1);

    //* Test3 (Sending float using UART) *//

//    float fl = 31.279806995999685f;
//    char test[4];
//    memcpy(&test, &fl, sizeof(fl));
//    for (char i = 0; i < 4; i++) UART_0_Write(test[i]);
//    green_on();
//    while (1);

    //* Test4 (Storing float in EEPROM) *//
    //float fl = 31.279806995999685f;
    //uint32_t test1;
    //memcpy(&test1, &fl, sizeof(fl));
    //EEPROM_go_to(0,0);
    //EEPROM_write(test1);
    //uint32_t test2 = EEPROM_read_word();
    //float fll;
    //memcpy(&fll, &test2, sizeof(test2));
    //if (fl == fll) green_on();
    //else red_on();
    //while (1);
}
