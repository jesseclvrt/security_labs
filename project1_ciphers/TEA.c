// Jesse Calvert
// CS430, 4/4/2019

/*
PROGRAM OUTPUT

Encrypting: 123456789abcdef
Ciphertext: a0761126d09724fd
Decrypted ciphertext: 123456789abcdef
*/

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#define DELTA 0x9E3779B9

void encrypt(uint32_t* key, uint32_t* p);
void decrypt(uint32_t* key, uint32_t* c);

int main() {
    uint32_t text[2] = {0x01234567, 0x89ABCDEF};
    uint32_t key[4] = {0xA56BABCD, 0x00000000, 0xFFFFFFFF, 0xABCDEF01};
    printf("Encrypting: %x%x\n", text[0], text[1]);
    encrypt(key, text);
    printf("Ciphertext: %x%x\n", text[0], text[1]);
    decrypt(key, text);
    printf("Decrypted ciphertext: %x%x\n", text[0], text[1]);
    return 0;
}

void encrypt(uint32_t* key, uint32_t* p) {
    uint32_t sum = 0;
    for (int i = 0; i < 32; i++) {
        sum += DELTA;
        p[0] += ((p[1]<<4) + key[0]) ^ (p[1] + sum) ^ ((p[1]>>5) + key[1]);
        p[1] += ((p[0]<<4) + key[2]) ^ (p[0] + sum) ^ ((p[0]>>5) + key[3]);
    }
}

void decrypt(uint32_t* key, uint32_t* c) {
    uint32_t sum = DELTA << 5;
    for (int i = 0; i < 32; i++) {
        c[1] -= ((c[0]<<4) + key[2]) ^ (c[0] + sum) ^ ((c[0]>>5) + key[3]);
        c[0] -= ((c[1]<<4) + key[0]) ^ (c[1] + sum) ^ ((c[1]>>5) + key[1]);
        sum -= DELTA;
    }
}