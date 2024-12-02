#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>

#define PORT 34852

int main()
{
    int mysocket;
    socklen_t socksize = sizeof(struct sockaddr_in);

    struct sockaddr_in serv;
    memset(&serv, 0, sizeof(serv));
    serv.sin_family = AF_INET;
    serv.sin_addr.s_addr = htonl(INADDR_ANY);
    serv.sin_port = htons(PORT);

    mysocket = socket(AF_INET, SOCK_STREAM, 0);

    bind(mysocket, (struct sockaddr *)&serv, sizeof(struct sockaddr));

    struct sockaddr_in client;

    listen(mysocket, 1);
    int consocket = accept(mysocket, (struct sockaddr *)&client, &socksize);

    const char *msg = "Hello, World!";

    while (consocket)
    {
        printf("Incoming connection from %s - Sending welcome!\n", inet_ntoa(client.sin_addr));
        send(consocket, msg, strlen(msg), 0);
        close(consocket);
        consocket = accept(mysocket, (struct sockaddr *)&client, &socksize);
    }

    close(mysocket);

    return EXIT_SUCCESS;
}
