#include <stdint.h>
#include <stdbool.h>
#include "tm4c123gh6pm.h"
#include "EEPROM.h"

bool EEPROM_Init(void) {
    SYSCTL_RCGCEEPROM_R = 0x1;
    for (int i = 0; i <=7; i++);
    while ((EEPROM_EEDONE_R & 0x01) != 0); 
    if ((EEPROM_EESUPP_R &0x0C) != 0) return false;
    SYSCTL_SREEPROM_R = 0x01;
    while (SYSCTL_PREEPROM_R == 0);
    while ((EEPROM_EEDONE_R & 0x01) != 0);
    if ((EEPROM_EESUPP_R &0x0C) != 0) return false;
    EEPROM_EEBLOCK_R = 0x0000;
    EEPROM_EEOFFSET_R = 0x0;
    return true;
}

void go_to(int block, int offset) {
    EEPROM_EEBLOCK_R = block;
    EEPROM_EEOFFSET_R = offset;
}

void go_to_block(int block) {
    EEPROM_EEBLOCK_R = block;
}

void go_to_word(int offset) {
    EEPROM_EEOFFSET_R = offset;
}

void write(char *data[4]) {
    
    EEPROM_EERDWR_R = data;
}

void write_with_increment(char *data[4]) {
    EEPROM_EERDWRINC_R = data;
}

void read_word(char *data[4]) {
    data = EEPROM_EERDWR_R;
}
void read_word_with_increment(char *data[4]) {
    data = EEPROM_EERDWRINC_R;
}