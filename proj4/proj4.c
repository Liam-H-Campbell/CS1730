#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <pthread.h>
#include "proj4.h"

/**
 * Initialize grid is called by main and reads a file to
 * store all the values to later be calculated by Diagonalsum
 *
 * @param grid is the grid to store the values in
 * @param file is the file to be read from.
 */
void initializeGrid(grid * g, char * fileName) {
    FILE *fptr;
    fptr = fopen(fileName, "r");
    char * line = NULL;
    size_t len = 0;
    ssize_t nread;
    int i = 0;

    while ((nread = getline(&line, &len, fptr)) != -1) {
        g->n = nread - 1;
        if (i == 0) {
            g->p = malloc(g->n * sizeof(unsigned char *));
            for (int k = 0; k < g->n; k++)
                g->p[k] = malloc(g->n * sizeof(unsigned char));
        }

        for (int j = 0; j < g->n; j++) {
            g->p[i][j] = line[j] - '0';
        }
        i++;
    }

    fclose(fptr);
    free(line);

}


/**
 * Thread arguments
 * @param input grid is the grid made by intializegrid
 * @param s is the sum supplied by the user.
 * @param start is the thread id.
 * @parma step is the number of threads.
 * @param back is the array that holds sums form left to right.
 * @param forward is teh array that holds sums from right ot left.
 */
typedef struct {
    grid * input;
    unsigned long s;
    int start;
    int step;
    int ** back;
    int ** forward;
} threadArgs;


/**
 * processDiagonals is the main driver of proj4.c
 * it can be a multithreaded process and processes from left to right
 * diagonals first then right to left last.
 * @param arg is the threadargs.
 *
 */
void * processDiagonals(void * arg) {
    threadArgs * a = (threadArgs *)arg;
    grid * input = a->input;
    unsigned long s = a->s;
    int n = input->n;

    // left to right
    // start is thread # and step is # of threads
    for (int d = a->start; d < 2*n - 1; d += a->step) {
        int offset = d - (n - 1);
        int row = (offset < 0) ? -offset : 0;
        int col = row + offset;
        int len = 0;
        int values[n];

        //values is a one dimensional array that matches a left to right diagonal at the starting
        //element p[row][col]
        while (row < n && col < n) {
            values[len] = input->p[row][col];
            len++;
            row++;
            col++;
        }


        for (int start = 0; start < len; start++) {
            int sum = 0;
            int active = 1; //acts as bool

            for (int end = start; end < len && active; end++) {
                sum += values[end];
                if (sum == s) {
                    for (int k = start; k <= end; k++) {
                        a->back[d][k] = 1; // sets back = 1 to rebuild later in diagonal
                    }
                    active = 0;
                }
                else if (sum > s) {
                    active = 0;
                }
            }
        }
    }

    // right to left
    for (int d = a->start; d < 2*n - 1; d += a->step) {
        int row = (d < n) ? 0 : d - (n - 1);
        int col = d - row;
        int len = 0;
        int values[n];

        while (row < n && col >= 0) {
            values[len] = input->p[row][col];
            len++;
            row++;
            col--;
        }

        for (int start = 0; start < len; start++) {
            int sum = 0;
            int active = 1; // acts as bool

            for (int end = start; end < len && active; end++) {
                sum += values[end];
                if (sum == s) {
                    for (int k = start; k <= end; k++) {
                        a->forward[d][k] = 1;
                    }
                    active = 0;
                }
                else if (sum > s) {
                    active = 0;
                }
            }
        }
    }

    return NULL;
}


/**
 * diagonalSums is called by main.
 *
 * builds all the required arrays for output then builds the thread arguments for
 * processdiagonals. After process diagonals has finished the method will
 * assemble the output grid from the two arrays back and forward, previously
 * manipulated in process method.
 *
 * @param input is the input grid.
 * @param s is the number to be sumed.
 * @param output is the output grid.
 * @param t is the number of threads.
 */
void diagonalSums(grid * input, unsigned long s, grid * output, int t) {
    int n = input->n;

    output->n = n;
    output->p = calloc(n, sizeof(unsigned char *));
    for (int i = 0; i < n; i++) {
        output->p[i] = calloc(n, sizeof(unsigned char));
    }

    int ** back  = calloc(2*n - 1, sizeof(int *));
    int ** forward = calloc(2*n - 1, sizeof(int *));

    pthread_t threads[t];
    threadArgs args[t];

    for (int d = 0; d < 2*n - 1; d++) {
        back[d] = calloc(n, sizeof(int));
        forward[d] = calloc(n, sizeof(int));
    }

    for (int i = 0; i < t; i++) {
        args[i].input = input;
        args[i].s = s;
        args[i].start = i;
        args[i].step = t;
        args[i].back = back;
        args[i].forward = forward;

        pthread_create(&threads[i], NULL, processDiagonals, &args[i]);
    }

    for (int i = 0; i < t; i++) {
        pthread_join(threads[i], NULL);
    }

    for (int d = 0; d < 2*n - 1; d++) {
        int offset = d - (n - 1);
        int row = (offset < 0) ? -offset : 0;
        int col = row + offset;
        int pos = 0;

        while (row < n && col < n) {
            if (back[d][pos] != 0) {
                output->p[row][col] = input->p[row][col];
            }
            pos++;
            row++;
            col++;
        }
    }

    for (int d = 0; d < 2*n - 1; d++) {
        int row = (d < n) ? 0 : d - (n - 1);
        int col = d - row;
        int pos = 0;

        while (row < n && col >= 0) {
            if (forward[d][pos] != 0) {
                output->p[row][col] = input->p[row][col];
            }
            pos++;
            row++;
            col--;
        }
    }

    for (int d = 0; d < 2*n - 1; d++) {
        free(back[d]);
        free(forward[d]);
    }
    free(back);
    free(forward);
}

/**
 * write grid takes the output grid from diagonal
 * and then writes every index to an output file supplied
 * by the user.
 *
 * @param g is the output grid.
 * @param fileName is the file supplied by the user.
 */
void writeGrid(grid * g, char * fileName) {
    FILE * fptr;
    fptr = fopen(fileName, "w");
    for (int i = 0; i < g -> n; i++) {
        for (int j = 0; j < g ->n; j++) {
            fprintf(fptr, "%d", g -> p[i][j]) ;
        }

        fprintf(fptr, "\n");
    }

    fclose(fptr);
}

/**
 * free grid is used to free the input and outputp
 * grids used in previous methods.
 *
 * @param g is the grid to be freed.
 */
void freeGrid(grid * g) {
    for (int i = 0; i < g -> n; i++) {
        free(g -> p[i]);
    }
    free(g -> p);
}
