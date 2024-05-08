bool EEPROM_Init(void);
void go_to(int block, int offset);
void go_to_block(int block);
void go_to_word(int offset);
void write(char *data[4]);
void write_with_increment(char *data[4]);
void read_word(char *data[4]);
void read_word_with_increment(char *data[4]);