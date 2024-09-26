#pragma once
#define LBA_SIZE 100

extern unsigned int ssd[LBA_SIZE];
 
void initialize_ssd();
void write_ssd(int lba, unsigned int value, char* buffer);
void read_ssd(int lba, char* buffer);
void full_write(unsigned int value, char* buffer);
void full_read(char* buffer);
int control(char* buffer);