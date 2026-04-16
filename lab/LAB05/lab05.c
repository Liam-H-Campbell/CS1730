#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>


/**
 * mask returns an int that is the maximum number that
 * fits within n bits. for instance n = 4 would be 15.
 *
 * @param n is the number of bits.
 * @return num is the maximum number that fits in n bits.
 */
int mask(unsigned int n) {
    int num = 1;
    for (int i = 0; i < n; i++) {
        num *= 2;
    } // for
    return --num;
} // mask

/**
 * this function turns a decimal number into a
 * bit string.
 *
 * @param long is the number to be turned into a string.
 * @param str is the character array to hold the string.
 */
void dtobstr(long num, char *str) {
    int i = strlen(str) - 1;

    while (num > 0 && i >= 0) {
        str[i] = (num % 2) + '0';
        num /= 2;
        i--;
    }
}


/**
 * This method is the driver when the user wants to
 * turn a decimal number into its binary representation
 * using a certain number of bits.
 *
 * @param num is the number to be turned into a bit string.
 * @param bit is the number of bits.
 */
void decToBin(long num, unsigned int bit) {
    long temp = num;
    char *str = calloc(bit + 1, sizeof(char));
    memset(str, '0', bit);
    str[strlen(str)] = 0;
    if (temp < 0) {
        temp = temp * -1;
        temp--;
        temp = ~temp;
        temp = temp & mask(bit);
    } // temp
    dtobstr(temp, str);
    printf("%ld in decimal is equal to %s in binary using %u-bit two's complement representation\n", num, str, bit);

    free(str);
} // decToBin



/**
 * main handles most of the user input so it then can be tranformed
 * into a bit string or a bit string can be transformed into a signed
 * decimal number.
 *
 * @param argc is the number of command line inputs.
 * @param argv is the array that holds the command line inputs.
 * @return 1 on failure.
 * @return 0 on success.
 */
int main(int argc, char *argv[]) {
    long num = 0;
    unsigned int bits = 0;
    if (strcmp(argv[1], "-bits") == 0) {
        num = atol(argv[4]);
        bits = atoi(argv[2]);
        decToBin(num,bits);
    } else if (strcmp(argv[1], "-decimal") == 0) {
        num = atol(argv[2]);
        bits = atoi(argv[4]);
        decToBin(num,bits);
    } else if (strcmp(argv[1], "-binary") == 0) {
        num = strtol(argv[2], 0 , 2);
        bits = strlen(argv[2]);
        if (argv[2][0] == '1') {
            num = ~num;
            num = num & mask(bits);
            num += 1;
            num = num * -1;
        } // if
        printf("%s in binary is equal to %ld in deciaml using %u-bit two's complement representation\n", argv[2], num, bits);
    } else {
        return 1;
    } // else
    return 0;
} // main
