#include <stdint.h>
#include <stdbool.h>
#include "tm4c123gh6pm.h"
#include "bit_utilies.h"
#include "EEPROM.h"

// Initialization function of EEPROM
bool EEPROM_Init(void) { // It returns if the EEPROM init is successful or not
    SET(SYSCTL_RCGCEEPROM_R,1);                     // Enables the clock
    for (int i = 0; i <=7; i++);                    // Halting loop
    while ((EEPROM_EEDONE_R & 0x01) != 0);          // Waiting for EEPROM operation
    if ((EEPROM_EESUPP_R & 0x0C) != 0)return false; // Check for EEPROM failure
    //CLR(SYSCTL_SREEPROM_R, 1);                      // Clear software reset bit
    //while (SYSCTL_PREEPROM_R == 0);                 // Checks if the EEPROM is ready
    //while ((EEPROM_EEDONE_R & 0x01) != 0);          // Waiting for EEPROM operation
    //if ((EEPROM_EESUPP_R &0x0C) != 0) return false; // Check for EEPROM failure
    EEPROM_EEBLOCK_R = 0x0000;                      // Start from Block #0
    EEPROM_EEOFFSET_R = 0x1;                        // at the start of the block
    return true; // Initialization successful
}
bool hold() {
    while ((EEPROM_EEDONE_R & 0x01) != 0);          // Waiting for EEPROM operation
    if ((EEPROM_EESUPP_R & 0x0C) != 0) return false;
    return true;
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
    hold();
}
// writes a 4-byte character array to the EEPROM and increments the offset
void EEPROM_write_with_increment(uint32_t word) {
    EEPROM_EERDWRINC_R = word;
    hold();
}

// reads a word from the EEPROM and put it in a character array
uint32_t EEPROM_read_word() {
    uint32_t readed = (uint32_t)EEPROM_EERDWR_R;
    hold();
    return readed;
}

// reads a word from the EEPROM and put it in a character array
// & then increments the block offset
uint32_t EEPROM_read_word_with_increment() {
    uint32_t readed = (uint32_t)EEPROM_EERDWRINC_R;
    hold();
    return readed;
}
// Reads until a null is found
void EEPROM_readall(char *arr) {
    EEPROM_go_to(0,0);
    uint32_t size = EEPROM_read_word_with_increment();
    uint32_t holder;
    char character;
    uint16_t counter = 0;
    uint32_t temp;
    while (1) {
        holder = EEPROM_read_word_with_increment();
        if (EEPROM_EEOFFSET_R == 0) EEPROM_EEBLOCK_R++;
        for (char i = 0; i < 4 ; i++) {
            temp = holder;
            character = (char)(temp >> (8 * (3 - i)));
            if (character == '\0' || counter == size -1) return;
            arr[counter] = character;
            counter++;
        }                                                                                                                                                                                                                                                                                                       
    }
}
// Writes an array of characters into EEPROM
void EEPROM_writeall(char *arr, uint16_t size) {
    EEPROM_go_to(0, 1); // Initialize EEPROM write pointer to start
    uint32_t temp;
    uint16_t counter = 0;
    while (size > 0) {
        uint16_t remainingByte = (size > 4) ? 4 : size; // Dete remaining Byte in bytes to process
        temp = 0;
        for (char i = 0; i < remainingByte; i++) {
            temp |= ((uint32_t)(*arr++) << ((3 - i) * 8)); // Construct 32-bit
            size--;
            counter++;
        }
        EEPROM_write_with_increment(temp); // Write to EEPROM and increment
        if (EEPROM_EEOFFSET_R == 0) EEPROM_EEBLOCK_R++; // Handle block increment
    }
    // Write the number of 32-bit words stored in the first word
    EEPROM_go_to(0, 0);
    EEPROM_write(counter);
}


// Mass erase the EEPROM
void EEPROM_MassErase() {
    SET(SYSCTL_SREEPROM_R,1);       // Set the software Reset register
    while ((EEPROM_EEDONE_R & EEPROM_EEDONE_WORKING) != 0);
    SET(EEPROM_EEDBGME_R, EEPROM_EEDBGME_ME);   // Set the mass erase bit
    while ((EEPROM_EEDONE_R & EEPROM_EEDONE_WORKING) != 0);
}