#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include "tm4c123gh6pm.h"
#include "bit_utilies.h"
#include "EEPROM.h"

bool EEPROM_Init(void) {
    SET(SYSCTL_RCGCEEPROM_R,1);
    for (int i = 0; i <=7; i++);
    while ((EEPROM_EEDONE_R & 0x01) != 0); 
    if ((EEPROM_EESUPP_R & 0x0C) != 0) return false;
    CLR(SYSCTL_SREEPROM_R, 1);
    while (SYSCTL_PREEPROM_R == 0);
    while ((EEPROM_EEDONE_R & 0x01) != 0);
    if ((EEPROM_EESUPP_R &0x0C) != 0) return false;
    EEPROM_EEBLOCK_R = 0x0000;
    EEPROM_EEOFFSET_R = 0x0;
    return true;
}

void EEPROM_go_to(int block, int offset) {
    EEPROM_EEBLOCK_R = block;
    EEPROM_EEOFFSET_R = offset;
}

void EEPROM_go_to_block(int block) {
    EEPROM_EEBLOCK_R = block;
}

void EEPROM_go_to_word(int offset) {
    EEPROM_EEOFFSET_R = offset;
}

void EEPROM_write(char *data) {
    uint32_t *i;
    i = data;
    EEPROM_EERDWR_R = *i;
}

void EEPROM_write_with_increment(char *data) {
    uint32_t *i;
    i = data;
    EEPROM_EERDWRINC_R = *i;
}

void EEPROM_read_word(char *arr) {
    uint32_t data = EEPROM_EERDWR_R;
    for (int i = 0; i < 4; i++) {
        arr[i] = (char)(data >> (8 * (3 - i)));
    }
}
void EEPROM_read_word_with_increment(char *arr) {
    uint32_t data = EEPROM_EERDWRINC_R;
    for (int i = 0; i < 4; i++) {
        arr[i] = (char)(data >> (8 * (3 - i)));
    }
}