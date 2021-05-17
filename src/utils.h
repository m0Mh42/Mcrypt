#ifndef UTILS_H
#define UTILS_H

#define BIN8_TEXT "%d%d%d%d%d%d%d%d"
#define b8tos(data)        \
    (data & 0x80 ? 1 : 0), \
    (data & 0x40 ? 1 : 0), \
    (data & 0x20 ? 1 : 0), \
    (data & 0x10 ? 1 : 0), \
    (data & 0x08 ? 1 : 0), \
    (data & 0x04 ? 1 : 0), \
    (data & 0x02 ? 1 : 0), \
    (data & 0x01 ? 1 : 0)

void clsetgreen();
void clsetred();
void clsetyellow();
void clreset();
void write_head(int, uint8_t*, FILE*);
int str_len(char*);
void randseed();
uint8_t randbyte();
void hash_to_string(char*, const uint8_t*);

#endif