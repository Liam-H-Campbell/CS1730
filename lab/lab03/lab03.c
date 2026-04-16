#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/**
 * given a long integer this method will turn
 * a number into a bit string and save it to a
 * character array.
 *
 * @param str is the string to house the bit string.
 * @param len is the length of the string.
 * @param n is the long integer to be turned into a bit string.
 */
void intToBin(char str[],char len, long n) {
    for (int i = len-1; i >= 0; i--) {
        char result = n % 2;
        if (result == 1) {
            str[i] = '1';
        } else {
            str[i] = '0';
        } // of
        printf("%c", str[i]);
        n = n/2;
    } // for
    printf("\n");
} //intToBin

/**
 * movedata moves characters to the end of an array
 * so it can later be padded with zeros.
 *
 * @param str is the characher array to be modified.
 * @param n is the number of shifts that a character will undergo.
 */
void movedata(char str[], char n) {
    for (int i = strlen(str)-1; i >= 0; i--) {
        str[i+n] = str[i];
        str[i] = 0;
    } // for

} // movedata

/**
 * padd adds zero until it reaches an already established
 * character which will appear at the value max.
 *
 * @param str is the string to be padded.
 * @param max is the first index containing vital information.
 */
void padd(char str[], char max) {
    for (int i = 0; i < max; i++) {
        str[i] = '0';
    } //for

} // padd

/**
 * main takes user input from the command line
 * and assumes that inputs are a bianry string form
 * of '1's and '0'
 * then modifies strings so that two strings are of the
 * the same length.
 * turns those strings into integer representations.
 * uses bitwise operations.
 * outputs important data.
 *
 * @param argc the number of command line args.
 * @param argv[] the array of command line args.
 * @return 1 if there are not enough command line args.
 * @return 0 on success.
 */
int main(int argc, char *argv[]) {
    if (argc < 4) {
        return 1;
    } // not enough information
    char maxLength;
    if (strlen(argv[1]) > strlen(argv[3])) {
        maxLength = strlen(argv[1]);
    } else {
        maxLength = strlen(argv[3]);
    } //else
    char *aStr = calloc(maxLength+1, sizeof(char));
    char *bStr = calloc(maxLength+1, sizeof(char));
    strcpy(aStr, argv[1]);
    strcpy(bStr, argv[3]);



    if (strlen(aStr) > strlen(bStr)) {
        char n = maxLength - strlen(bStr);
        movedata(bStr, n);
        padd(bStr, n);
    } else if (strlen(aStr) < strlen(bStr)) {
        char n = maxLength - strlen(aStr);
        movedata(aStr, n);
        padd(aStr, n);
    } // if

    unsigned long a = strtol(aStr, 0, 2);
    unsigned long b = strtol(bStr, 0, 2);
    unsigned long c;
    char opp;
    if (strcmp(argv[2],"-and") == 0) {
        c = a & b;
        opp = '&';
    } else if (strcmp(argv[2], "-or") == 0) {
        c = a | b;
        opp = '|';
    } else if (strcmp(argv[2], "-xor") == 0) {
        c = a ^ b;
        opp = '^';
    } // if
    char *cStr = calloc(maxLength+1, sizeof(char));
    intToBin(cStr,maxLength, c);
    printf("%s %c %s evaluates to %s using bit strings of length %u\n", aStr, opp, bStr, cStr, maxLength);
    printf("%lu %c %lu evaluates to %lu using unsigned %u-bit integers\n", a, opp, b, c, maxLength);
    return 0;
} // main
