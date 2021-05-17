#include <stdlib.h>

#include "header.h"

u_int8_t magicbytes[4] = {
    0x85, 0x69, 0xC4, 0x18
};

u_int8_t secondheader[8] = {
    0b11111111, //year
    0b11110000, //month
    0b00001111, 0b10000000, // day
    0b01111100, //hour
    0b00000011, 0b11110000, //min
    0b00001111 // count
}; 

int check_magicbytes(u_int8_t bytes[4]){
    for (int i = 0; i < 4; i++){
        if(bytes[i] != magicbytes[i]) 
            return 0;
    }
    return 1;
}

void create_magicbytes(u_int8_t bytes[4]){
    bytes[0] = magicbytes[0];
    bytes[1] = magicbytes[1];
    bytes[2] = magicbytes[2];
    bytes[3] = magicbytes[3];
}

struct SecondHeaderType parse_secondheader(u_int8_t bytes[4]){
    u_int8_t year = bytes[0] & secondheader[0];
    u_int8_t month = (bytes[1] & secondheader[1]) >> 4;
    u_int8_t day = ((bytes[1] & secondheader[2]) << 1) + ((bytes[2] & secondheader[3]) >> 7);
    u_int8_t hour = (bytes[2] & secondheader[4]) >> 2;
    u_int8_t min = ((bytes[2] & secondheader[5]) << 4) + ((bytes[3] & secondheader[6]) >> 4);
    u_int8_t count = bytes[3] & secondheader[7];
    struct SecondHeaderType header;
    header.year = year;
    header.month = month;
    header.day = day;
    header.hour = hour;
    header.min = min;
    header.count = count;
    return header;
}

void create_secondheader(struct SecondHeaderType header, u_int8_t bytes[4]){
    bytes[0] = header.year;
    bytes[1] = header.month << 4;
    bytes[1] += header.day >> 1;
    bytes[2] = header.day << 7;
    bytes[2] += header.hour << 2;
    bytes[2] += header.min >> 4;
    bytes[3] = header.min << 4;
    bytes[3] += header.count;
}