#include <stdio.h>
#include <stdlib.h>
#include <netdb.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>
#define PORT 8784
#define BUFFER_SIZE 1024

int main()
{
    int sockfd, clen, clientfd;
    int exit_code = 0;
    int connected = 0;
    char y_n[1];
    char send_buffer[BUFFER_SIZE];
    char recv_buffer[BUFFER_SIZE];
    struct sockaddr_in saddr, caddr;
    unsigned short port = PORT;
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        perror("Failed to create socket");
    }
    memset(&saddr, 0, sizeof(saddr));
    saddr.sin_family = AF_INET;
    saddr.sin_addr.s_addr = htonl(INADDR_ANY);
    saddr.sin_port = htons(port);
    if (bind(sockfd, (struct sockaddr *)&saddr, sizeof(saddr)) < 0)
    {
        perror("Binding error");
        return 1;
    }
    if (listen(sockfd, 5) < 0)
    {
        perror("Listening error");
        return 1;
    }
    clen = sizeof(caddr);
    printf("Listening on port: %d\n", port);
    while (1)
    {
        while (1)
        {
            printf("Waiting for connection...\n");
            if ((clientfd = accept(sockfd, (struct sockaddr *)&caddr, &clen)) < 0)
            {
                perror("Connection erorr");
                return 1;
            }
            else
            {
                printf("A client connected, IP address: %s\n", inet_ntoa(caddr.sin_addr));
                connected = 1;
                break;
            }
        }

        printf("You are now chatting with %s\n", inet_ntoa(caddr.sin_addr));
        memset(send_buffer, 0, BUFFER_SIZE);
        memset(recv_buffer, 0, BUFFER_SIZE);
        while (1)
        {
            fflush(stdout);
            fflush(stdin);
            memset(recv_buffer, 0, sizeof(recv_buffer));
            printf("Waiting for response from client...\n");
            do
            {
                if (recv(clientfd, recv_buffer, BUFFER_SIZE, 0) == 0)
                {
                    printf("Client disconnected!\n");
                    connected = 0;
                    fflush(stdout);
                    fflush(stdin);
                    close(clientfd);
                    break;
                }
                //recv(clientfd, recv_buffer, BUFFER_SIZE, 0);
                if (strcmp(recv_buffer, "closed\n") == 0)
                    {
                        printf("Connection closed!\n");
                        printf("Client disconnected!\n");
                        exit_code = 1;
                        break;
                    }
                printf("Response: %s", recv_buffer);
            } while (recv_buffer[strlen(recv_buffer) - 1] != '\n');

            if (exit_code == 1)
            {
                break;
            }

            if (connected == 0)
            {
                break;
            }
            printf("Enter your message: ");
            do
            {
                fgets(send_buffer, BUFFER_SIZE, stdin);
                // send_buffer[strlen(send_buffer) - 1] = '\0';
                // printf("send: %s", send_buffer);
                if (strcmp(send_buffer, "/exit\n") == 0)
                {
                    strcpy(send_buffer, "plsclose\n");
                    printf("Closing client connection...\n");
                    send(clientfd, send_buffer, strlen(send_buffer) + 1, 0);
                    break;
                }
                if (strcmp(send_buffer, "/dc\n") == 0)
                {
                    strcpy(send_buffer, "plsclose\n");
                    printf("Closing client connection...\n");
                    send(clientfd, send_buffer, strlen(send_buffer) + 1, 0);
                    connected = 0;
                    break;
                }
                send(clientfd, send_buffer, strlen(send_buffer) + 1, 0);
                printf("Message sent!\n");
            } while (send_buffer[strlen(send_buffer) - 1] != '\n');
            memset(send_buffer, 0, sizeof(send_buffer));
            fflush(stdout);
            fflush(stdin);
            if (connected == 0)
            {
                break;
            }
            // printf("exit_code: %d\n", exit_code);
        }
        if (exit_code == 1)
        {
            break;
        }
    }
    shutdown(clientfd, SHUT_RDWR);
    shutdown(sockfd, SHUT_RDWR);
    close(clientfd);
    close(sockfd);
    printf("Exiting...\n");
    return 0;
}