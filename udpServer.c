#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
int main()
{
    struct sockaddr_in6 server_addr;
    server_addr.sin6_family = AF_INET6;
    server_addr.sin6_port = htons(8888);
    server_addr.sin6_addr=in6addr_any;

    struct sockaddr_in6 peer_addr;
/*    
    struct sockaddr_in6 dest_addr;
    dest_addr.sin6_family = AF_INET6;
    dest_addr.sin6_port = htons(8888);
    dest_addr.sin_addr.s_addr = inet_addr("192.168.2.13");
*/
    int tmp = 0;
    char buf[1024] = {0};
    int addrLen = sizeof(struct sockaddr_in);

    //1 创建socket文件
    int sockfd = socket(AF_INET6,SOCK_DGRAM,0);
    if(sockfd < 0)
    {
        perror("socket creat error! \n");
    }
    else
    {
        printf("socket successful\n");
    }
    //2 绑定(标识自己在网络上的名字)
    tmp = bind(sockfd,(struct sockaddr *)&server_addr,sizeof(server_addr));
    if(tmp<0)
    {
        perror("socket bind error! \n");
    }
    else
    {
        printf("bind successful\n");
    }
    //3 收/发
    while(1)
    {
        memset(buf,0,sizeof(buf));
        //收
        printf("prepare recv\n");
        tmp = recvfrom(sockfd,buf,sizeof(buf),0,(struct sockaddr *)&peer_addr,(socklen_t *)&addrLen);
        if(tmp<0)
            perror("socket recv error! \n");
        else
        {
            printf("recv successful\n");
//            printf("recv from ip is = %s,port is = %d\n",inet_ntoa(peer_addr.sin6_addr),ntohs(peer_addr.sin6_port));
            printf("recv buf is = %s\n",buf);
        }

        //发
/*
        strcpy(buf,"I have recv your message successful!\n");
        tmp = sendto(sockfd,buf,strlen(buf),0,(struct sockaddr *)&peer_addr,addrLen);
        if(-1 == tmp)
            perror("socket send error! \n");
*/
    }
	
	close(sockfd);
    return 0;
}
