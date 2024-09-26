#pragma once
#include <stdint.h>
//extern uint8_t *key;

void AES_Decrypt(uint8_t* input, uint32_t* output);
void AES_Encrypt(uint32_t input, uint8_t* output);