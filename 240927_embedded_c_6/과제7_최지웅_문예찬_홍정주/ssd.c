#define _CRT_SECURE_NO_WARNINGS
#define CRYPTO
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ssd.h"
#include <stdint.h>
#include "Crypto.h"

#define LBA_SIZE 100

unsigned int ssd[LBA_SIZE];

void initialize_ssd() {
    FILE* nand_file = fopen("nand.txt", "r");
    if (nand_file == NULL) {
        for (int i = 0; i < LBA_SIZE; i++) {
            ssd[i] = 0x00000000;
        }
    }
    else {
        for (int i = 0; i < LBA_SIZE; i++) {
#ifdef CRYPTO
            uint32_t out;
            //for (int j = 0; j < 16; j++) fscanf_s(nand_file, "%02X", &in[j]);
            char input[34];
            uint8_t in[16];

            fgets(input, 34, nand_file);
            char tmp[3] = { 0 };
            for (int i = 0; i < 16; i++) {
                tmp[0] = input[i * 2];
                tmp[1] = input[i * 2 + 1];
                in[i] = strtol(tmp, NULL, 16);
            }
            input[32] = 0;
            /*printf("%d: %s\n",i, input);*/
            AES_Decrypt(in, &out);
            ssd[i] = out;
           /* printf("out: %08X\n", ssd[i]);*/
            
#else
            fscanf_s(nand_file, "%08X", &ssd[i]);
#endif
        }
        fclose(nand_file);
    }
}

void write_ssd(int lba, unsigned int value, char* buffer) {
    if (lba < 0 || lba >= LBA_SIZE) {
        printf("Error: Invalid LBA %d\n", lba);
        return;
    }
    ssd[lba] = value;

    FILE* nand_file = fopen("nand.txt", "w");
    if (nand_file == NULL) {
        sprintf(buffer,"Error: Cannot open nand.txt\n");
        return;
    }

    for (int i = 0; i < LBA_SIZE; i++) {
#ifdef CRYPTO
        uint8_t out[16];// 
        AES_Encrypt(ssd[i], out);
        for (int i = 0; i < 16; i++) fprintf(nand_file, "%02X", out[i]);
        fprintf(nand_file, "\n");
#else
        fprintf(nand_file, "%08X\n", ssd[i]);
#endif
    }

    fclose(nand_file);
    sprintf(buffer, "Wrote value 0x%08X to LBA %d", value, lba);
}

void read_ssd(int lba, char* buffer ) {
    if (lba < 0 || lba >= LBA_SIZE) {
        sprintf(buffer,"Error: Invalid LBA %d\n", lba);
        return;
    }
    sprintf(buffer, "0x%08X\n", ssd[lba]);
}

// Full Write 명령어 처리 함수
void full_write(unsigned int value, char* buffer) {
    for (int i = 0; i < LBA_SIZE; i++) {
        ssd[i] = value;
    }

    // nand.txt 파일에 기록
    FILE* nand_file = fopen("nand.txt", "w+");
    if (nand_file == NULL) {
        sprintf(buffer,"Error: Cannot open nand.txt\n");
        return;
    }

    for (int i = 0; i < LBA_SIZE; i++) {
        //fprintf(nand_file, "%08X\n", ssd[i]); // 각 LBA의 값을 파일에 기록
#ifdef CRYPTO
        uint8_t out[16];// 
        AES_Encrypt(ssd[i], out);
        for (int i = 0; i < 16; i++) fprintf(nand_file, "%02X", out[i]);
        fprintf(nand_file, "\n");
#else
        fprintf(nand_file, "%08X\n", ssd[i]);
#endif
    }
    fclose(nand_file);
    sprintf(buffer, "Full write completed with value 0x%08X\n", value);
}

// Full Read 명령어 처리 함수
void full_read(char* buffer) {
    strcpy(buffer, "");
    for (int i = 0; i < LBA_SIZE; i++) {
        char tmp[15];
        sprintf(tmp, "%02d %08X\n",i, ssd[i]); // LBA에서 읽은 값 출력
        strcat(buffer, tmp);
    }
    printf("Full read completed\n");
}





//initialize_ssd();



int control(char* buffer) {

    char* ssd = strtok(buffer, " ");
    char* command = strtok(NULL, " ");
    if (!ssd || !command) {
        sprintf(buffer, "Error: Unknown command %s", buffer);
        return 1;
    }


    if (strcmp(command, "W") == 0) {
        char* address = strtok(NULL, " ");
        char* data = strtok(NULL, " ");
        int lba = atoi(address);
        unsigned int value = (unsigned int)strtoul(data, NULL, 16);
        write_ssd(lba, value, buffer);
    }
    else if (strcmp(command, "R") == 0) {
        char* address = strtok(NULL, " ");
        int lba = atoi(address);
        read_ssd(lba, buffer);
    }
    else if (strcmp(command, "fullwrite") == 0) {
        char* data = strtok(NULL, " ");
        unsigned int value = (unsigned int)strtoul(data, NULL, 16);
        full_write(value,buffer);
        strcpy(buffer, "Full wirte completed.");
    }
    else if (strcmp(command, "fullread") == 0) {
        full_read(buffer);
    }

    else {
        sprintf(buffer, "Error: Unknown command %s", buffer);
        return 1;
    }

    return 0;

}