#include <stdio.h>
#include <stdlib.h>
#include <netdb.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>

#define PORT 8784
#define BUFFER_SIZE 1024

int main()
{
    int sockfd, clen, clientfd;
    char send_buffer[BUFFER_SIZE];
    char recv_buffer[BUFFER_SIZE];
    struct sockaddr_in saddr, caddr;
    unsigned short port = PORT;
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
        perror("Binding error!\n");
        return 1;
    }
    if (listen(sockfd, 5) < 0)
    {
        perror("Listening error!\n");
        return 1;
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
        else
        {
            printf("A client connected, IP address: %s\n", inet_ntoa(caddr.sin_addr));
            break;
        }
    }
    printf("You are now chatting with %s\n", inet_ntoa(caddr.sin_addr));
    memset(send_buffer, 0, BUFFER_SIZE);
    memset(recv_buffer, 0, BUFFER_SIZE);
    while(1)
    {
        fflush(stdout);
        fflush(stdin);
        memset(recv_buffer, 0, sizeof(recv_buffer));
        printf("Waiting for response from client...\n");
        recv(clientfd, recv_buffer, BUFFER_SIZE, 0);
        printf("Response: %s \n", recv_buffer);
        printf("Enter your message: "); 
        fgets(send_buffer, BUFFER_SIZE, stdin);
        send_buffer[strlen(send_buffer) - 1] = '\0';
        // printf("%s", send_buffer);
        if(strcmp(send_buffer,"/exit")==0)
        {
            printf("Exiting...\n");
            break;
        }
        send(clientfd, send_buffer, strlen(send_buffer), 0);
        memset(send_buffer, 0, sizeof(send_buffer));
        fflush(stdout);
        fflush(stdin);
    }
    return 0;
}