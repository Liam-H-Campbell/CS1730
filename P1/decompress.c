#include <stdio.h>
#include <stdlib.h>



/**
 * inToChar matches a number to a character
 * given a number.
 * @param n is the number to be matched.
 * @return A,T,C,G depending on the number.
 */
char intToChar(int n) {
    if (n == 0) {
        return 'A';
    } else if (n == 1) {
        return 'T';
    } else if (n == 2) {
        return 'C';
    } else {
        return 'G';
    } // if else if

} // intToChar

/**
 * decompress is given a number array and turns
 * said array into a DNA string. calls inTochar to
 * match numbers with chars.
 *
 * @param nums is the integer array to be decompressed.
 */
void decompress(int *nums) {

    int length = nums[0];
    char *str = calloc(length + 1, sizeof(char));
    int pos = 0;
    int full = (length + 3) / 4;
    for (int i = 1; i <= full && pos < length; i++) {
        unsigned char num = nums[i];
        for (int j = 0; j < 4 && pos < length; j++) {
            int n = (num >> (6 - 2*j)) & 3;
            str[pos++] = intToChar(n);
        } // for
    } // for

    printf("%s\n", str);
    free(str);
}
