#include <complex.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>

#define MAXRCVLEN 500
#define PORT 34852

int main()
{
    int mysocket;
    mysocket = socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in serv;
    memset(&serv, 0, sizeof(serv));
    serv.sin_family = AF_INET;
    serv.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
    serv.sin_port = htons(PORT);

    connect(mysocket, (struct sockaddr *)&serv, sizeof(struct sockaddr_in));

    char buffer[MAXRCVLEN + 1];
    int len = recv(mysocket, buffer, MAXRCVLEN, 0);

    buffer[len] = '\0';

    printf("Received %s (%d bytes).\n", buffer, len);

    close(mysocket);
    return EXIT_SUCCESS;
}
