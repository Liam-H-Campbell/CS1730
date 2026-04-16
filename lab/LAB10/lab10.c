#include <signal.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>


double sum = 0; // sum is used to hold the total value provided by input
char * line = NULL; // line holds input so it can be turned into a double and added to sum


void sigh(int sig); // prototype

/**
 * adds numbers provided by the user or file.
 *
 * file either waits 60 seconds after a file is finished
 *
 * or waits for a signal to terminate the program
 *
 * @param argc # of arguments
 * @param argv list of arguments
 * @return 0 on success.
 */
int main(int argc, char **argv) {

    pid_t pid = getpid();
    printf("Program started with pid = %d.\n", pid);

    printf("Enter a list of doubles to sum,\n"
           "and to end the program,\n"
           "run one of the following Unix commands:\n"
           "  kill -8 %d\n"
           "  kill -10 %d\n"
           "  kill -12 %d\n", pid, pid, pid);

    signal(8,  sigh);
    signal(10, sigh);
    signal(12, sigh);

    double value;
    size_t len = 0;


    while (getline(&line, &len, stdin) != -1) {

        if (sscanf(line, "%lf", &value) == 1) {
            sum += value;
        } else {
            printf("Error: please input a numeric value.\n");
        } // if else

    } // while

    sleep(60);
    printf("The sum is: %lf\n", sum);
    printf("Program ended after sleeping for 60 seconds.\n");
    return 0;
}


/**
 * signal handler for the program.
 * when an appropriate signal is sent
 * prints the sum and prints the signal and pid
 * exits
 *
 * @param sig is the sinal number.
 */
void sigh(int sig) {
    printf("The sum is: %lf\n", sum);
    printf("Program ended by handling the signal from kill -%d %d\n", sig, getpid());
    free(line);
    exit(0);
}
