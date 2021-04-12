#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int file_length(FILE *file){
    fseek(file, 0, SEEK_END);
    int length = ftell(file);
    rewind(file);
    return length;
}

int main(int argc, char *argv[]){
    if (argc < 4){
        printf("Usage: %s [file1] [file2] [password]", argv[0]);
        return -1;
    }
    FILE *fp;
    char *data;
    fp = fopen(argv[1], "rb");
    int len = file_length(fp);
    data = malloc(len);
    int i = 0;
    while (!feof(fp)){
        data[i++] = fgetc(fp);
    }
    fclose(fp);
    fp = fopen(argv[2], "wb");
    int pass = (uintptr_t)argv[3];
    for (int j = 0; j < i-1; j++){
        fputc((data[j] ^ pass), fp);
    }
    fclose(fp);
    return 0;
}
