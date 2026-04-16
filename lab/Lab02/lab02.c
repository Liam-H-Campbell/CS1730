#include <stdio.h>
#include <stdlib.h>


void decToBin(long num, char bin[]); //prototype
int distance(char one[], char two[]); //prototype
int findLength(char bin[]); // prototype


/**
 * converts a decimal to a vector of characters
 * with either a value of zero or one.
 * representing its binary number.
 *
 * @param num the number to be converted.
 * @param bin the array to hold the binary string.
 */
void decToBin(long num, char bin[]) {
    for (int i = 63; i >= 0; i--) {
        bin[i] = (num % 2) + '0';
        num /= 2;
    }
    bin[64] = '\0';
} // decToBin
/**
 * finds the hamming distance between
 * two binary strings by comparing each element
 * in the array at the same index.
 *
 * @param one the first araay to be compared.
 * @param two the second array to be compared.
 * @return the number of bits that differ between the two arrays.
 */
int distance(char one[], char two[]) {
    int n = 0;
    for (int i = 0; i < 64; i++) {
        if (one[i] != two[i]) {
            n++;
        }
    }
    return n;
} // distance

/**
 * finds where the most significant bit is in the larger
 * binary string.
 *
 * @param bin is the array that corresponds to the larger decimal number.
 * @return the distance from the end of the array and the most significant bit.
 */
int findLength(char bin[]) {
    for (int i = 0; i < 64; i++) {
        if (bin[i] == '1') {
            return 64 - i;
        }
    }
    return 1;
} // findLength

/**
 * used to convert commmand line arguments that are long integers
 * into binary strings.
 *
 * @param argc is the amount of command line arguments.
 * @param argv is the array of command line arguments.
 * @return 0 if successful.
 * @return 1 if unsuccessful.
 */
int main(int argc, char *argv[]) {
    if (argc < 3) {
        printf("please provide two integers\n");
        return 1;
    }

    long x = atol(argv[1]);
    long y = atol(argv[2]);

    char xBin[65];
    char yBin[65];

    decToBin(x, xBin);
    decToBin(y, yBin);

    int len;

    if (x > y) {
        len = findLength(xBin);
    } else {
        len = findLength(yBin);
    } // else



    printf("%.*s is the bit string for %ld\n", len, xBin + (64 - len), x);
    printf("%.*s is the bit string for %ld\n", len, yBin + (64 - len), y);

    int dist = distance(xBin, yBin);
    printf("%d is the hamming distance between the bit strings\n", dist);

    return 0;
} // main
