#include <stdio.h>
#include <stdlib.h>

// p is a pointer that is used to test the sum function.
int * p;

/*
 * Return the sum of the n values in x starting at index 0.
 * If x is NULL, then return -1.
 * If n is 0 and x is not NULL, then return 0.
 */
int sum(int * x, int n);

/**
 * main takes command line inputs then stores 1 - n in
 * an integer array.
 * main then outputs the first element of the array.
 * and the sum of the array.
 * then attempts to sum the global pointer p which is a null pointer.
 * sum returns -1.
 *
 * @param arc is the number of arguments.
 * @param argv is the array of arguments.
 * @return 0 on success.
 */
int main(int argc, char * argv[]){
  // x should point to a new array of ints stored on the heap
    int * x = malloc(sizeof(int) * argc); //changed this line to malloc.
    for(int i = 0; i < argc-1; i++){ //changed this line to be argc-1 because we dont want argv[0].
        x[i] = atoi(argv[i+1]); // atoi instead of type casting.
  }

  printf("*x is %d\n", *(x+0));
  int y = sum(x, argc-1); // argc-1
  printf("y is %d\n", y);
  int z = sum(p, argc-1); // arc-1
  printf("z is %d\n", z);
  free(x);
  return 0;
}

/**
 * sum return the sum of an array
 * if the pointer is valid.
 * if the pointer has no value then it
 * will return -1;
 *
 * @param x is the pointer.
 * @param n is the size of the array.
 * @return sum if successful.
 * @return -1 if the pointer is NULL.
 */
int sum(int * x, int n){
    if (x == NULL) {
        return -1; // null check
    } // if
    int sum = 0; // set sum == 0
  for(int i = 0; i < n; i++) {
      sum = sum + *(x+i);
  }
  return sum; // return sum
}
