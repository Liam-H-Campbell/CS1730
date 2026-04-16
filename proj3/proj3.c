#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>


void step1(FILE *ptr1, FILE *ptr2, long size1, long size2); //prototype

void step2(FILE *ptr1, FILE *ptr2, long size1, long size2); //prototype


/**
 * main opens two files and checks if they are valid.
 * if the files are valid then the attempts to compare and
 * write the differences to files.
 *
 * @param argc is the number of args.
 * @param argv is an array holding the args.
 * @return 1 on failure. 0 on success.
 */
int main(int argc, char ** argv) {

    if(argc != 3) {
        printf("Usage: proj3.out <file1> <file2>\n");
        exit(1);
    } // if

    FILE *f1ptr;
    FILE *f2ptr;

    f1ptr = fopen(argv[1],"r");
    f2ptr = fopen(argv[2],"r");

    if (f1ptr == NULL || f2ptr == NULL) {
        printf("There was an error reading a file.\n");
        return 1;
    } // if

    long size1;
    long size2;
    struct stat st; // struct to find the file size of different files
    stat(argv[1], &st);
    size1 = (long)st.st_size;
    stat(argv[2], &st);
    size2 = (long)st.st_size;

    struct timeval start1, start2, end1, end2; // struct to find the start and end times of steps

    gettimeofday(&start1, NULL);
    step1(f1ptr,f2ptr,size1,size2);
    gettimeofday(&end1, NULL);

    rewind(f1ptr);
    rewind(f2ptr);

    gettimeofday(&start2, NULL);
    step2(f1ptr,f2ptr,size1,size2);
    gettimeofday(&end2, NULL);

    fclose(f1ptr);
    fclose(f2ptr);
    double time1 = (end1.tv_sec - start1.tv_sec) + ((end1.tv_usec - start1.tv_usec) / 1000000.0);
    double time2 = (end2.tv_sec - start2.tv_sec) + ((end2.tv_usec - start2.tv_usec) / 1000000.0);

    printf("Step 1 took %lf milleseconds\n", time1);
    printf("Step 2 took %lf milleseconds\n", time2);

    return 0;
} // main



/**
 * step1 compares to files by reading a character at a time
 * and using a buffer of 2.
 * the program will terminate if there is no text file to write to.
 *
 * @param ptr1 file1.
 * @param ptr2 file2.
 * @param size1 is the size of file1 in bytes.
 * @param siz2 is the size of file2 in bytes.
 */
void step1(FILE *ptr1, FILE *ptr2, long size1, long size2) {
    FILE *dptr = fopen("differencesFoundInFile1.txt", "w");
    if (dptr == NULL) {
        printf("There was an error writing to a file\n");
        exit(1);
    } // if

    for (long i = 0; i < size1; i++) {
        char * str1 = calloc(2, sizeof(char));
        char * str2 = calloc(2, sizeof(char));


        str1[0] = (char)getc(ptr1);

        if (i < size2) {

            str2[0] = (char)getc(ptr2);
            if (str1[0] != str2[0]) {
                fwrite(str1, 1, 1, dptr);
            }
        } else {

            fwrite(str1, 1, 1, dptr);
        }

        free(str1);
        free(str2);
    } // for

    fclose(dptr);
} // step1


/**
 * step2 reads the entirety of a file to an array.
 * then compares each element of the array and writes
 * the differences to a file.
 *
 * @param ptr1 is file1.
 * @param ptr2 is file2.
 * @param size1 is the size of file1 in bytes.
 * @param size2 is the size of file2 in bytes.
 */
void step2(FILE *ptr1, FILE *ptr2, long size1, long size2) {
    FILE *dptr = fopen("differencesFoundInFile2.txt", "w");
    if (dptr == NULL) {
        printf("There was an error writing to a file\n");
        exit(1);
    } // if

    char * str1 = malloc(sizeof(char) * size1);
    char * str2 = malloc(sizeof(char) * size2);

    fread(str1,1,size1,ptr1);
    fread(str2,1,size2,ptr2);

    for (long i = 0; i < size2; i++) {

        if (i < size1) {
            if (str1[i] != str2[i]) {
                fputc(str2[i],dptr);
            } // if
        } else {
            fputc(str2[i],dptr);
        } // if - else

    } // for

    fclose(dptr);
    free(str1);
    free(str2);

} //step2;
