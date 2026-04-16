#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "compress.h"
#include "decompress.h"


/**
 * main takes command line input and manipulates it so
 * it can either be compressed or decompressed.
 *
 * @param argc is the number of arguments.
 * @parma argv is the array of arguments.
 * @return 0 if successful;
 * @return 1 if there is incorrect input.
 */
int main(int argc, char *argv[]) {
    if (strcmp(argv[1], "-c") == 0) {
        char *str = calloc(strlen(argv[2]) + 1, sizeof(char));
        strcpy(str, argv[2]);
        str[strlen(str)] = 0;
        compress(str,strlen(str));
    } else if (strcmp(argv[1], "-d") == 0) {
        int *nums = calloc(argc-2, sizeof(int));
        for (int i = 0; i < argc-2; i++) {
            unsigned char num = atoi(argv[i+2]);
            nums[i] = num;
        } //  for
        decompress(nums);
    } else {
        return 1;
    }

    return 0;
} // main
