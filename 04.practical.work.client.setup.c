#include <stdio.h>
#include <stdlib.h>
#include <netdb.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#define PORT 8784
#define MAX_LENGTH 255

int main(int argc, char **argv)
{
    int sockfd, clen, clientfd;
    struct sockaddr_in saddr, caddr;
    unsigned short port = PORT;
    char domain[MAX_LENGTH];
    char ip_addr[32];
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
    return(0);
}
