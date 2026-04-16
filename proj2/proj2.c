#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


/**
 * copy copies the array into a new array 40 bytes larger than
 * the previous array. then prints from what memory location it copied to
 * and from.
 *
 * @param grades is the array to be copied from.
 * @param temp is the array to be copied to.
 * @param count is the number of elements in the array.
 */
void copy(double * grades, double * temp, int count) {
    for (int i = 0; i < count; i++) {
        *(temp+i) = *(grades+i);
    } // for
    printf("Copied %d grades from %p to %p\n", count, (void *) grades, (void*) temp);
    printf("Freed %d bytes from the heap at %p\n", count * 8, (void *) grades);
} // copy

/**
 * allocate makes a new a array 40 bytes larger than the
 * previous one then calls copy if the array has elements and
 * frees the old array.
 * sets the old array to the new one.
 *
 * @param grades is the old array.
 * @param count is the number of elements.
 */
void allocate(double ** grades, int count) {
    double * temp = malloc((count+5) * sizeof(double));
    printf("Allocated %d bytes from the heap at %p\n", (count + 5) * 8, (void *) temp);
    if (count != 0) {
        copy(*grades, temp, count);
        free(*grades);
    } // if
    * grades = temp;
} // allocate


/**
 * printGrade iterates throughout the whole array and compares
 * wether that element is greater than or equal to the average or
 * less than the average then prints it to the user.
 *
 * @param avg is the average.
 * @param grades is the array.
 * @param count is the number of elements.
 */
void printGrade(double avg, double * grades, int count) {
    for (int i = 0; i < count; i++) {
        if (*(grades+i) >= avg) {
            printf("%d. The grade of %lf is >= the average.\n", i + 1, *(grades+i));
        } else {
            printf("%d. The grade of %lf is < the average.\n", i + 1, *(grades+i));
        }
    } // for
} // printGrade

/**
 * main uses scanf to take grade inputs from the user.
 * then stores them in an array that grows larger by
 * 40 bytes every time the array is full.
 *
 * @return 0 if successful.
 */
int main() {
    printf("Enter a list of grades below where each grade is seperated by a newline character.\n");
    printf("After the last grade is entered, enter a negative value to end the list.\n");

    double * grades;
    int count = 0;
    double avg  = 0;
    double n;
    int all = 0;
    int deall = 0;
    int bytes = 0;
    int lastall = 0;


    scanf("%lf",&n);
    while (n >= 0) {
        if (bytes == 0) {
            allocate(&grades, count);
            bytes += 40;
            lastall = 40;
            all++;
        } // if

        *(grades+count) = n;
        printf("Stored %lf in the heap at %p\n",n, (void *) (grades + count));
        count++;
        avg += n;

        if (count % 5 == 0) {
            printf("Stored %d grades (%d bytes) to the heap at %p\n",count, bytes, (void *) grades);
            printf("Heap at %p is full.\n",(void *) grades);
            allocate(&grades,count);
            bytes += (count/5 + 1) * 40;
            lastall = (count/5 + 1) * 40;
            all++;
            deall++;
        } // if

        scanf("%lf", &n);
    } // while

    if (count == 0) {
        avg = 0;
        printf("The average of %d grades is %lf.\n",count,avg);

    } else {
        avg = avg / count;
        printf("The average of %d grades is %lf.\n",count,avg);
        printGrade(avg,grades,count);
        printf("Freed %d bytes from the heap at %p\n",lastall , (void *) grades);
        free(grades);
        deall++;
    } // if - else

    printf("total heap usage: %d allocs, %d frees, %d bytes allocated\n", all, deall, bytes);
    return 0;
} // main
