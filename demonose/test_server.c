#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>          /* See NOTES */
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h> /* superset of previous */
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#define ROWS 120
#define COLUMNS 10
int main(int argc, const char *argv[])
{
    int sockfd = socket(AF_INET6,SOCK_STREAM,0);
    struct sockaddr_in6 server_addr;
    server_addr.sin6_family = AF_INET6;
    server_addr.sin6_port = htons(8888);
    if (inet_pton(AF_INET6,"2409:8955:ccc:7272:20c:29ff:fe07:3025", &server_addr.sin6_addr) < 0 ) 
    {                 // IPv6
        perror("inet_pton err");
        return -1;
    }
    bind(sockfd,(struct sockaddr*)&server_addr,sizeof(server_addr));
    listen(sockfd,10);
    struct sockaddr_in6 peer_addr;
    socklen_t len = sizeof(peer_addr);
    int new_sockfd = accept(sockfd,(struct sockaddr *)&peer_addr,&len);
    if(new_sockfd < 0)
    {
        perror("accept err");
        exit(-1);
    }
    else
    {
        printf("new_sockfd = %d\n",new_sockfd);
        double recvmsg[ROWS][COLUMNS];
        memset(recvmsg,0,sizeof(recvmsg));
        char *pRecvmsg =(char *)&recvmsg[0][0];
        int res= recv(new_sockfd,pRecvmsg,sizeof(double)*(ROWS*COLUMNS),0);
        if(res < 0)
        {
            perror("recv err");
            return -1;
        }
        else
        {
            int i=0,j=0;
            for(i=0;i<ROWS;i++)
            {
                for(j=0;j<COLUMNS;j++)
                {
                    printf(" %lf ",recvmsg[i][j]);
                }
                putchar('\n');
            }
        }
    }
    return 0;
}
