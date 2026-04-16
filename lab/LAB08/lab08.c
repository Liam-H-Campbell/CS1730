#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void printFloat(int num); // prototype
void printDouble(long num); //prototype

/**
 * Holds to unions to facilitate the printingn of
 * the binary representation of either a double
 * or a float.
 *
 * @param int argc is the number of command line args.
 * @param argv is the array that holds command line args.
 */
int main(int argc, char * argv[]) {

    union {
        float num1;
        int num2;
    } ieeeF;

    union {
        double num1;
        long num2;
    } ieeeD;

    if(strcmp(argv[1], "-f") == 0) {
        ieeeF.num1 = atof(argv[2]);

        printf("%f encoded in binary using a 32 bit IEEE 754 encoding is below.\n",ieeeF.num1);
        printFloat(ieeeF.num2);
    } else {
         ieeeD.num1 = atof(argv[2]);

         printf("%lf encoded in binary using a 64 bit IEEE 754 encoding is below.\n",ieeeD.num1);
         printDouble(ieeeD.num2);
    }

    return 0;
} // main


/**
 * print float is given a 4 byte integer
 * then prints all bits in said integer.
 *
 * @param num the integer.
 */
void printFloat(int num) {
   for (int i = 31; i >= 0; i--) {
       printf("%d", (num >> i) & 1);
   } // for
   printf("\n");
   for (int i = 31; i >= 0; i--) {
       if (i == 31) {
           printf("sign bit:\t   ");
       }
       printf("%d", (num >> i) & 1);
       if (i == 31) {
           printf("\nexponent (8 bit):  ");
       }
       if (i == 23) {
           printf("\nfraction (23 bit): ");
       } //if
   } // for
   printf("\n");
} // printFloat

/**
 * printDouble is given an 8 byte integer
 * then prints all bits in said integer.
 *
 * @param num is the integer to be printed.
 */
void printDouble(long num) {
    for (int i = 63; i >= 0; i--) {
        printf("%ld", (num >> i) & 1);
    } // for
    printf("\n");
    for (int i = 63; i >= 0; i--) {
        if (i == 63) {
            printf("sign bit:\t   ");
        }
        printf("%ld", (num >> i) & 1);
        if (i == 63) {
            printf("\nexponent (11 bit): ");
        }
        if (i == 52) {
            printf("\nfraction (52 bit): ");
        } //if
    } // for
    printf("\n");
} // printDouble
