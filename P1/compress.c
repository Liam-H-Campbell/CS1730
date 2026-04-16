#include <stdio.h>
#include <stdlib.h>

/**
 * finds the correct size of an array
 * by repeatedly subtracting 4.
 *
 * @param n is the number of chancters in a string.
 * @return size which is the size of the array.
 */
int arrSize(int n) {
    int temp = n;
    int size = 1;
    while (temp != 0) {
        if (temp <= 4) {
            temp = 0;
            size++;
        } else {
            temp -= 4;
            size++;
        } // else
    } // while
    return size;
} // arrSize

/**
 * matches characters with their corresponding numbers.
 *
 * @param c is the character to be mathed to a number.
 * @return 0,1,2,3 depending on the number.
 */
char charToInt(char c) {
    if (c == 'A') {
        return 0;
    } else if (c == 'T') {
        return 1;
    } else if (c == 'C') {
        return 2;
    } else {
        return 3;
    }
} // charToInt

/**
 * prints an integer array.
 *
 * @param nums is the array to be printed.
 * @param size is the size of nums.
 */
void printInts(int *nums, int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", nums[i]);
    }
    printf("\n");
} // printInts

/**
 * main force behind compression, calls helper methods
 * to find size of arrays, match numbers with letters, and
 * printing compressed number array.
 *
 * @param str is the string to be compressed.
 * @param is the length of the string.
 */
void compress(char *str, int n) {
    int size = arrSize(n);
    int *nums = calloc(size, sizeof(int));
    nums[0] = n;
    int temp = n;
    int last = 0;
    for (int i = 1; i < size; i++) {
        if (temp < 4) {
            last = temp;
        } // if
        unsigned char num = 0;
        for (int j = 0; j < 4; j++) {
            if (temp >= 0) {
                num |= charToInt(str[n - temp]);
                temp--;
            }
            if (j != 3) {
                num <<= 2;
            } // if
        }
        if (i == size - 1 && last != 0) {
            last = 4 - last;
            num >>= last*2;
            num <<= last*2;
        }
        nums[i] = num;
    }
    printInts(nums,size);

} // compress
