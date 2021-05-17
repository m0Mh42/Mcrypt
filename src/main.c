#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <time.h>

#include "sha-256.h"
#include "header.h"
#include "utils.h"

int main(int argc, char *argv[]){

    // No password of file
    if (argc < 3){
        clsetred();
        printf("Usage: %s [file] [password]\n", argv[0]);
        clreset();
        return -1;
    }

    // File names
    int outputfilenamelen = str_len(argv[1]) + 5; // 4 + 1 (null char)
    char outputfilename[outputfilenamelen];
    strcpy(outputfilename, argv[1]);
    strcat(outputfilename, ".cyp");
    
    // File streams
    FILE* inputfile;
    FILE* outputfile;

    // Open input file.
    inputfile = fopen(argv[1], "rb");
    if (!inputfile){
        clsetred();
        perror("Input File Error");
        clreset();
        exit(127);
    }

    // Input file header
    uint8_t inputmagicbytes[4];
    uint8_t inputsecondheader[4];
    uint8_t randbytes[2];

    // Reading input file magic bytes (first 4 bytes)
    for (int i = 0; i < 4; i++) {
        inputmagicbytes[i] = fgetc(inputfile);
    }
    if (check_magicbytes(inputmagicbytes)){
        // For count
        for (int i = 0; i < 4; i++) {
            inputsecondheader[i] = fgetc(inputfile);
        }
    } else {
        // Not a re-encryption
        rewind(inputfile);
        memset(inputsecondheader, 0, 4);
    }

    // Rand bytes seeding
    randseed();
    randbytes[0] = randbyte();
    randbytes[1] = randbyte();
    
    // Header set
    struct SecondHeaderType header;
    uint8_t headerstr[4];
    
    // Uncompleted second headering
    header.year = 0;
    header.month = 0;
    header.day = 0;
    header.hour = 0;
    header.min = 0;
    header.count = (inputsecondheader[3] & 0x0F) + 1;
    create_secondheader(header, headerstr);

    // Password hashing
    uint8_t hash[32];
    calc_sha_256(hash, argv[2], strlen(argv[2]));

    // Opening output file
    outputfile = fopen(outputfilename, "wb");
    if (!outputfile){
        clsetred();
        perror("Output File Error");
        clreset();
        exit(128);
    }

    // Writing headers to output file.
    write_head(4, magicbytes, outputfile);
    write_head(4, headerstr, outputfile);
    write_head(2, randbytes, outputfile);

    clsetgreen();
    printf("Encrypting... ");
    fflush(stdout);

    uint8_t c;
    while(!feof(inputfile)) {
        c = fgetc(inputfile);
        
        // We don't have 0xff in ascii table.
        if (c == 0xFF) break; 

        c ^= randbytes[0];

        for (int i = 0; i < 32; i++){
            c ^= hash[i];
        }

        c ^= randbytes[1]; // Not an easy reversibility.

        fputc(c, outputfile);
    }

    printf("Done!\n");
    clreset();

    printf("File encrypted and saved in '%s'\n", outputfilename);

    // Closing :P
    fclose(inputfile);
    fclose(outputfile);
    return 0;
}
