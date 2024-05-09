#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <math.h>
#include "tm4c123gh6pm.h"
#include "bit_utilies.h"
#include "EEPROM.h"

// Initialization function of EEPROM
bool EEPROM_Init(void) { // It returns if the EEPROM init is successful or not
    SET(SYSCTL_RCGCEEPROM_R,1);                     // Enables the clock
    for (int i = 0; i <=7; i++);                    // Halting loop
    while ((EEPROM_EEDONE_R & 0x01) != 0);          // Waiting for EEPROM operation
    if ((EEPROM_EESUPP_R & 0x0C) != 0)return false; // Check for EEPROM failure
    CLR(SYSCTL_SREEPROM_R, 1);                      // Clear software reset bit
    while (SYSCTL_PREEPROM_R == 0);                 // Checks if the EEPROM is ready
    while ((EEPROM_EEDONE_R & 0x01) != 0);          // Waiting for EEPROM operation
    if ((EEPROM_EESUPP_R &0x0C) != 0) return false; // Check for EEPROM failure
    EEPROM_EEBLOCK_R = 0x0000;                      // Start from Block #0
    EEPROM_EEOFFSET_R = 0x0;                        // at the start of the block
    return true; // Initialization successful
}
// Goes to the specified block and word
void EEPROM_go_to(int block, int offset) {
    EEPROM_EEBLOCK_R = block;
    EEPROM_EEOFFSET_R = offset;
}
// Goes to the specified block with the same offset
void EEPROM_go_to_block(int block) {
    EEPROM_EEBLOCK_R = block;
}
// Goes to the specified word within the same block
void EEPROM_go_to_word(int offset) {
    EEPROM_EEOFFSET_R = offset;
}
// writes a 4-byte character array to the EEPROM
void EEPROM_write(uint32_t word) {
    EEPROM_EERDWR_R = word;
}
// writes a 4-byte character array to the EEPROM and increments the offset
void EEPROM_write_with_increment(uint32_t word) {
    EEPROM_EERDWRINC_R = word;
}
// reads a word from the EEPROM and put it in a character array
uint32_t EEPROM_read_word() {
    return (uint32_t)EEPROM_EERDWR_R;
}
// reads a word from the EEPROM and put it in a character array
// & then increments the block offset
uint32_t EEPROM_read_word_with_increment() {
    return (uint32_t)EEPROM_EERDWRINC_R;
}
// Reads until a null is found
void EEPROM_readall(char *arr, uint16_t size) {
    uint32_t holder;
    char character;
    while (1) {
        uint16_t counter = 0;
        holder = EEPROM_read_word_with_increment();
        if (EEPROM_EEOFFSET_R == 0) EEPROM_EEBLOCK_R++;
        for (uint16_t i = 0; i < 4 ; i++) {
            character = (char)(holder >> (8 * (3 - i)));
            if (character == null || counter == size -1) return;
            arr[counter] = character;
            counter++;
        }
    }
}
// Writes an array of characters into EEPROM
void EEPROM_writeall(char *arr, uint16_t size) {
    uint32_t *words;
    words = arr;
    uint16_t wordsize = roundf(size/4.0f) -1;
    uint8_t rem = size%4;
    while (1) {
        if (EEPROM_EEOFFSET_R == 0) EEPROM_EEBLOCK_R++;
        for (uint16_t m = 0; m < wordsize; m++) {
            EEPROM_write_with_increment(words[m]);
        }
        holder = words[wordsize] >> (8*rem);
        holder = holder << (8*rem);
        EEPROM_write_with_increment(holder);
    }
}