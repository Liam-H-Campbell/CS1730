#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

/**
 * main uses command line arguments to initialize local variables
 * ip, port, and message.
 * ip and port are used to connect to a server and then the message is
 * sent to said server.
 *
 * @param argc is the number of arguments
 * @param argv is the array of arguments
 * @return 0 on success 1 on failure
 */
int main(int argc, char ** argv) {
    char * ip = argv[1];
    int port  = atoi(argv[2]);
    char * message = argv[3];
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in addr = {0};
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    addr.sin_addr.s_addr = inet_addr(ip);

    if (connect(sockfd, (struct sockaddr *)&addr, sizeof(addr)) < 0) {
        perror("connect\n");
        close(sockfd);
        return 1;
    }


    send(sockfd, message, strlen(message), 0);

    close(sockfd);
    return 0;

} // main
