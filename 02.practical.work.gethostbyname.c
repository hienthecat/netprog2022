#include <stdio.h>
#include <stdlib.h>
#include <netdb.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>

#define MAX_LENGTH 255

int main(int argc, char *argv[])    
{
    printf("GET HOST BY DOMAIN NAME v0.1\n");
    char domain[MAX_LENGTH];
    char ip_addr[32];
    struct hostent *hostInfo;
    int boolean=0;
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
        printf("Host not found!\n");
    }
    else 
    {
    for(int i = 0; hostInfo -> h_addr_list[i] != NULL; i++)
        {
            struct in_addr *ip_addr;
            ip_addr = (struct in_addr *)(hostInfo->h_addr_list[i]);
            printf("The domain %s has the following address: %s\n",domain,inet_ntoa(*ip_addr));
        }
    }
    printf("Exitting...\n");
    return(0);

    // while(1)
    // {
    // printf("Please enter a domain name: ");
    // fgets(domain, MAX_LENGTH, stdin);
    // domain[strlen(domain) - 1] = '\0';
    // printf("%s\n",domain);
    // hostInfo = gethostbyname(domain);
    // if (hostInfo == NULL)
    // {
    //     printf("Host not found!\n");
    //     continue;
    // }
    // else 
    // {
    // for(int i = 0; hostInfo -> h_addr_list[i] != NULL; i++)
    //     {
    //         struct in_addr *ip_addr;
    //         ip_addr = (struct in_addr *)(hostInfo->h_addr_list[i]);
    //         printf("The domain %s has the following address: %s\n",domain,inet_ntoa(*ip_addr));
    //         continue;
    //     }
    // }
    
    // printf("\nDo you want to resolve another domain?\nType ""1"" for yes: ");
    // scanf("%d",&boolean);
    // if(boolean != 1)
    // {
    //     printf("Exitting...\n");
    //     break;
    // }
    // else
    // {
    //     fflush(stdin);
    //     continue;
    // }
    // }
}