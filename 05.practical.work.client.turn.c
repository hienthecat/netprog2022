#include <stdio.h>
#include <stdlib.h>
#include <netdb.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#define PORT 8784
#define MAX_LENGTH 255
#define BUFFER_SIZE 1024

int main(int argc, char **argv)
{
    int sockfd, clen;
    struct sockaddr_in saddr, caddr;
    unsigned short port = PORT;
    char domain[MAX_LENGTH];
    char ip_addr[32];
    char send_buffer[BUFFER_SIZE];
    char recv_buffer[BUFFER_SIZE];
    struct hostent *hostInfo;
    if(argc>1)
    {
        strncpy(domain,argv[1],MAX_LENGTH);
    }
    else
    {
        printf("Please enter a domain name: ");
        fgets(domain, MAX_LENGTH, stdin);
        domain[strlen(domain) - 1] = '\0';
    }
    hostInfo = gethostbyname(domain);
    if (hostInfo == NULL)
    {
        perror("Host not found!\n");
        return 1;
    }
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        perror("Failed to create socket!\n");
        return 1;
    }
    memset(&saddr, 0, sizeof(saddr));
    saddr.sin_family = AF_INET;
    saddr.sin_addr.s_addr = htonl(INADDR_ANY);
    saddr.sin_port = htons(port);
    memcpy((char *)&saddr.sin_addr.s_addr, hostInfo->h_addr_list[0], hostInfo->h_length);
    if (connect(sockfd, (struct sockaddr *)&saddr, sizeof(saddr)) < 0)
    {
        perror("Connection error!\n");
        return 1;
    }
    printf("Connected to %s\n", inet_ntop(hostInfo->h_addrtype, hostInfo->h_addr_list[0], ip_addr, sizeof(ip_addr)));
    printf("You are now chatting with %s\n",inet_ntop(hostInfo->h_addrtype, hostInfo->h_addr_list[0], ip_addr, sizeof(ip_addr)));
    memset(send_buffer, 0, sizeof(send_buffer));
    memset(recv_buffer, 0, sizeof(recv_buffer));
    while(1)
    {
        //printf("%s", recv_buffer);
        fflush(stdout);
        fflush(stdin);
        //printf("send %s", send_buffer);
        printf("Enter a message: ");
        fgets(send_buffer, BUFFER_SIZE, stdin);
        send_buffer[strlen(send_buffer) - 1] = '\0';
        // printf("%s", send_buffer);
        if(strcmp(send_buffer,"/exit")==0)
        {
            printf("Exiting...\n");
            break;
        }
        send(sockfd,send_buffer,strlen(send_buffer) + 1,0);
        memset(send_buffer, 0, sizeof(send_buffer));
        memset(recv_buffer, 0, sizeof(recv_buffer));
        printf("Waiting for response from server...\n");
        recv(sockfd,recv_buffer,BUFFER_SIZE,0);
        printf("Response: %s \n",recv_buffer);
        //printf("recv %s \n", recv_buffer);
        //memset(recv_buffer, 0, sizeof(recv_buffer));
        fflush(stdout);
        fflush(stdin);
    }
    return(0);
}
