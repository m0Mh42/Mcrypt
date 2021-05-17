#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <time.h>

#include "utils.h"

void clsetgreen(){
    printf("\033[0;32m");
}

void clsetred(){
    printf("\033[0;31m");
}

void clsetyellow(){
    printf("\033[0;33m");
}

void clreset(){
    printf("\033[0m");
}

void write_head(int l, uint8_t* str, FILE* fp){
    for(int i = 0; i < l; i++){
        fputc(str[i], fp);
    }
}

int str_len(char* __restrict__ string){
    int i = 0;
    while(string[i] != 0){
        i++;
    }
    return i++;
}

void randseed(){
    srand(time(NULL));
}

uint8_t randbyte(){
    uint8_t n = rand();
    return n;
}

void hash_to_string(char string[65], const uint8_t hash[32]){
    for (int i = 0; i < 32; i++){
        string += sprintf(string, "%02x", hash[i]);
    }
}

