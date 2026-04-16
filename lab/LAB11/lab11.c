#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <sys/wait.h>
#include <unistd.h>


/**
 * Main sorts command line arguments into seperate commands
 * if there is a -pipe present in the list of arguments.
 * if there is no pipe there is one command and it will run the single
 * command.
 * if there is a -pipe the output of the first command will be
 * piped into the second acting as a unix command.
 *
 * @param argc is the number of arguments.
 * @param argv is the list of arguments.
 * @return 0 on success.
 */
int main(int argc, char ** argv) {

    bool cmd = true;
    int cmd1 = 1;
    int cmd2 = 1;
    int index = argc;
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-pipe") != 0) {
            if (cmd) {
                cmd1++;
            } else {
                cmd2++;
            }
        } else {
            index = i;
            cmd = false;
        }
    }


    char * cmd_one[cmd1 + 1];
    for (int i = 0; i < cmd1 - 1; i++) {
        cmd_one[i] = argv[i + 1];
    }
    cmd_one[cmd1 - 1] = NULL;


    if (index == argc) {
        execvp(cmd_one[0], cmd_one);
        perror("execvp failed");
        return 0;
    }


    char * cmd_two[cmd2 + 1];
    for (int i = 0; i < cmd2 - 1; i++) {
        cmd_two[i] = argv[index + 1 + i];
    }
    cmd_two[cmd2 - 1] = NULL;

    int fd[2];
    pipe(fd);

    pid_t pid = fork();
    perror("fork failed");

    if (pid == 0) {
        dup2(fd[1], STDOUT_FILENO);
        close(fd[0]);
        close(fd[1]);
        execvp(cmd_one[0], cmd_one);
        perror("execvp cmd_one failed");
    } else {
        dup2(fd[0], STDIN_FILENO);
        close(fd[0]);
        close(fd[1]);
        execvp(cmd_two[0], cmd_two);
        perror("execvp cmd_two failed");
        wait(NULL);
    }

    return 0;
}
