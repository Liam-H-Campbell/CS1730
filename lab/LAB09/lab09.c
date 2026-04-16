#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>



/**
 * main uses fork to make a child that runs ps
 * then after the parent function runs ./countdown.out
 * with a previously supplied command line argument.
 *
 *
 * @param argc is the number of command line args
 * @param argv is the array that holds arguments
 * @return 1 on failure 0 on success.
 */
int main(int argc, char *argv[]) {
    printf("The parent's PID is %d.\n", getpid());
    printf("The parent is now forking.\n");

    pid_t pid = fork();

    if (pid == 0) {

        printf("The child's PID is %d.\n", getpid());
        printf("The child is executing ps.\n");
        char * args[] = {"ps", NULL};
        char * env[] = {NULL};
        execve("/usr/bin/ps", args,env);

    } else {

        wait(NULL);
        printf("The parent waited patiently for its child to complete.\n");
        printf("The parent is executing ./countdown.out %s.\n", argv[1]);
        char * args[]  = {"./countdown.out", argv[1], NULL};
        char * env[] = {NULL};
        execve("./countdown.out", args, env);
    }

    return 0;
}
