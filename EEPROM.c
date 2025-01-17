#include <stdint.h>
#include <stdbool.h>
#include "tm4c123gh6pm.h"
#include "bit_utilies.h"
#include "EEPROM.h"

// Initialization function of EEPROM
bool EEPROM_Init(void) { // It returns if the EEPROM init is successful or not
	int i;
    SET(SYSCTL_RCGCEEPROM_R,1);	// Enables the clock
		
    for ( i = 0; i <=7; i++);                    // Halting loop
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
	uint32_t size;
    uint32_t holder;
	char i;
	char character;
    uint16_t counter = 0;
    uint32_t temp;
    EEPROM_go_to(0,0);
    size = EEPROM_read_word_with_increment();   // Retrieve the size of the array stored
    while (1) {
        holder = EEPROM_read_word_with_increment(); // retrieve a word from the EEPROM
        if (EEPROM_EEOFFSET_R == 0) EEPROM_EEBLOCK_R++; // Handle block increment
				
        for (i = 0; i < 4 ; i++) {  // fetch the characters from each word
            temp = holder;
            character = (char)(temp >> (8 * (3 - i)));
            if (character == '\0' || counter == size -1) return;  // check for reaching the end of the data
            arr[counter] = character;   // stores the character inside the array
            counter++;
        }                                                                                                                                                                                                                                                                                                       
    }
}
// Writes an array of characters into EEPROM
void EEPROM_writeall(char *arr, uint16_t size) {
	uint32_t temp;
    uint16_t counter = 0;
	uint16_t remainingByte;
    EEPROM_go_to(0, 1); // Initialize EEPROM write pointer to start
    while (size > 0) {
        char i;
        remainingByte = (size > 4) ? 4 : size; // Dete remaining Byte in bytes to process
        temp = 0;
			
        for (i = 0; i < remainingByte; i++) {   // Stores the char in a holder word
            temp |= ((uint32_t)(*arr++) << ((3 - i) * 8)); 
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