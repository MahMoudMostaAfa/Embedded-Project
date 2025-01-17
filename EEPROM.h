#ifndef EEPROM_H
#define EEPROM_H

bool EEPROM_Init(void);
void EEPROM_go_to(int block, int offset);
void EEPROM_go_to_block(int block);
void EEPROM_go_to_word(int offset);
void EEPROM_write(uint32_t word);
void EEPROM_write_with_increment(uint32_t word);
uint32_t EEPROM_read_word();
uint32_t EEPROM_read_word_with_increment();
void EEPROM_writeall(char *arr, uint16_t size);
void EEPROM_readall(char *arr);
void EEPROM_MassErase();

#endif /*EEPROM_H*/
