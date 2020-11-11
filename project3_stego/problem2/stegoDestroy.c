/*
 * Jesse Calvert
 * CS430 4/28/2019
 * 
 * Destroys information hidden in .bmp files using stego.c
 * stegoRead.c will only output an empty file.
 */

#include <stdio.h>
#include <stdlib.h>

#define START_FROM 100

int main(int argc, const char *argv[]) {

    if (argc != 3) {
        fprintf(stderr, "\nUsage: %s stegoImage output\n\n", argv[0]);
        fprintf(stderr, "where stegoImage == file with information to destroy\n");
        fprintf(stderr, "      output == filename of output\n\n");
        exit(0);
    }

    char temp;

    FILE* input = fopen(argv[1], "r");
    FILE* output = fopen(argv[2], "w");
    for (int i = 0; i < START_FROM; i++) { //skip START_FROM bytes
        fscanf(input, "%c", &temp);
        fprintf(output, "%c", temp);
    }

    int x;
    while (fscanf(input, "%c", &temp) == 1) {
        temp &= ~1; //clear lsb
        fprintf(output, "%c", temp);
    }
    fprintf(stdout, "Stego destroyed.\n");
}