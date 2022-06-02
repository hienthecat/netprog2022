#include <stdio.h>
#include <stdlib.h>
#include <netdb.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>

int main()
{
    int sockfd, clen, clientfd;
    struct sockaddr_in saddr, caddr;
    unsigned short port = 8784;
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        printf("Failed to create socket!\n");
    }
    memset(&saddr, 0, sizeof(saddr));
    saddr.sin_family = AF_INET;
    saddr.sin_addr.s_addr = htonl(INADDR_ANY);
    saddr.sin_port = htons(port);
    if (bind(sockfd, (struct sockaddr *)&saddr, sizeof(saddr)) < 0)
    {
        printf("Binding error!\n");
    }
    if (listen(sockfd, 5) < 0)
    {
        printf("Listening error!\n");
    }
    clen = sizeof(caddr);
    printf("Listening on port %d...\n", port);
    while (1)
    {
        if ((clientfd = accept(sockfd, (struct sockaddr *)&caddr, &clen)) < 0)
        {
            perror("Connection erorr!\n");
            return 1;
        }

        printf("A client connected, IP address: %s\n", inet_ntoa(caddr.sin_addr));
    }
}