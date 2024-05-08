bool EEPROM_Init(void);
void EEPROM_go_to(int block, int offset);
void EEPROM_go_to_block(int block);
void EEPROM_go_to_word(int offset);
void EEPROM_write(char *data);
void EEPROM_write_with_increment(char *data);
void EEPROM_read_word(char *arr);
void EEPROM_read_word_with_increment(char *arr);