#ifndef HEAD_H
#define HEAD_H

// Header be like:
// MAGIC BYTES:
//      First 4 bytes: 0x85 0x69 0xC4 0x18
//      Second 4 bytes: 
//          first 17 bits for Date: 8 for year, 4 for month, 5 for day
//          second 11 bits for Time: 5 for hour, 6 for minutes
//          third 4 bits for count
// SEQUENCED XORS;
//      First 1 byte for first xor.
//      Second 1 byte for third xor.

extern u_int8_t magicbytes[4];

extern u_int8_t secondheader[8];

struct SecondHeaderType {
    u_int8_t year, month, day, hour, min, count;
};

// 4 + 4 + 64 + 1
int check_magicbytes(u_int8_t bytes[4]);
void create_magicbytes(u_int8_t bytes[4]);
struct SecondHeaderType parse_secondheader(u_int8_t bytes[4]);
void create_secondheader(struct SecondHeaderType header, u_int8_t bytes[4]);

#endif
