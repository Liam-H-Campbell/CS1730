#include <stdio.h>
#include <string.h>
#include <stdlib.h>


/**
 * intToBit turns a given integer into
 * a bit string. the given bitstring is
 * full of placeholder zeros.
 *
 * @param str is the string to hold the bit string.
 * @param num is the number to be converted to binary.
 */
void intToBit(char* str, int num) {
    int temp = num;
    int i = strlen(str) - 1;
    while (temp > 0 && i >= 0) {
        if (temp % 2 == 1) {
            str[i] = '1';
        } else {
            str[i] = '0';
        } //of
        temp = temp /2;
        i--;
    }

} // intToBit


/**
 * this function manipulates a string so that
 * all the values in said string are moved the left
 * n times. index 0 is filled with a '0' and
 * the final index is dropped.
 *
 * @param str is the string to be manipulated.
 * @param n is the number of shifts.
 */
void leftshift(char* str, int n) {
    int len = strlen(str);
    for (int i = 0; i < n; i++) {
        char temp1 = '0';
        for (int j = len-1; j > -1; j--) {
            char temp2 = str[j];
            str[j] = temp1;
            temp1 = temp2;
        }
    }

} // leftshift

/**
 * this function manipulates a string so that all the
 * values in said string are move to the right n
 * times.
 * the last index is filled with a '0' and index 0 is
 * dropped
 *
 * @param str is the string to be manipulated.
 * @param n is the number of shifts.
 */
void rightshift(char *str, int n) {
    int len = strlen(str);
    for (int i = 0;  i < n; i++) {
        char temp1 = '0';
        for (int j = 0; j < len; j++) {
            char temp2 = str[j];
            str[j] = temp1;
            temp1 = temp2;
        } // for
    } // for
}

/**
 * range is used to calculate the mask for
 * bitwise operators. it takes the length of the given
 * string to calculate it.
 * in the form of 2^length -1.
 *
 * @param count is the length of the string.
 */
long range(int count) {
    long n = 1;
    for (int i = 0; i < count; i++) {
        n = n * 2;
    } // for
    n--;
    return n;
} // range


/**
 * flip is used to change 1s and 0s acting as
 * the string manipulator for bitwise not.
 *
 * @param str is the string to be manipulated.
 */
void flip(char *str) {
    for (int i = 0; i < strlen(str); i++) {
        if (str[i] == '0') {
            str[i] = '1';
        } else if (str[i] == '1') {
            str[i] = '0';
        } // else if

    } // for

} // flip


/**
 * main takes user input from the command line
 * and assumes that inputs are a bianry string form
 * of '1's and '0', and an opperator and the corresponding
 * integer if the user wants to shift a string.
 * the main method then does two changes one
 * based on string manipulation and the other
 * based on bitwise opps.
 * outputs important data.
 *
 * @param argc the number of command line args.
 * @param argv[] the array of command line args.
 * @return 0 on success.
 * @return 1 on failure.
 */
int main(int argc, char *argv[]) {
    if (strcmp(argv[1], "-not") == 0) {
        char bitstr[65];
        char tempstr[65];
        strcpy(bitstr,argv[2]);
        strcpy(tempstr,argv[2]);
        flip(tempstr);
        long val1 = strtol(bitstr, 0, 2);
        long val2 = ~ val1;
        long n = range(strlen(bitstr));
        val2 = n & val2;
        printf("~%s evaluates to %s using bit strings of length %lu\n", bitstr, tempstr, strlen(bitstr));
        printf("~%lu evaluates to %lu using unsigned %lu-bit integers\n", val1, val2, strlen(bitstr));

    } else if (strcmp(argv[2], "-leftshift") == 0) {
        char bitstr[65];
        char tempstr[65];
        strcpy(bitstr, argv[1]);
        strcpy(tempstr, bitstr);
        int shifts = atoi(argv[3]);
        leftshift(tempstr, shifts);
        long val1 = strtol(bitstr, 0, 2);
        long val2 = val1 << shifts;
        long n = range(strlen(bitstr));
        val2 = val2 & n;
        char shiftstr[strlen(bitstr)+1];
        memset(shiftstr,'0',strlen(bitstr));
        shiftstr[strlen(bitstr)] = 0;
        intToBit(shiftstr, shifts);
        printf("%s << %s evaluates to %s using bit strings of length %lu\n", bitstr,shiftstr, tempstr, strlen(bitstr));
        printf("%lu << %d evaluates to %lu using unsigned %lu-bit integers\n", val1, shifts, val2, strlen(bitstr));

    } else if (strcmp(argv[2], "-rightshift") == 0) {
        char bitstr[65];
        char tempstr[65];
        strcpy(bitstr, argv[1]);
        strcpy(tempstr, bitstr);
        int shifts = atoi(argv[3]);
        rightshift(tempstr, shifts);
        long val1 = strtol(bitstr, 0, 2);
        long val2 = val1 >> shifts;
        long n = range(strlen(bitstr));
        val2 = val2 & n;
        char shiftstr[strlen(bitstr)+1];
        memset(shiftstr,'0',strlen(bitstr));
        shiftstr[strlen(bitstr)]  = 0;
        intToBit(shiftstr, shifts);
        printf("%s >> %s evaluates to %s using bit strings of length %lu\n", bitstr,shiftstr, tempstr, strlen(bitstr));
        printf("%lu >> %d evaluates to %lu using unsigned %lu-bit integers\n", val1, shifts, val2, strlen(bitstr));

    } else {
        printf("Please enter a bit string and operator in the form \'001\' (-not, -leftshift, -rightshift)\n");
        return 1;
    } // else
    return 0;
} // main
