#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>
//0 在写这段代码的时候，当你遇到htons(),inet_addr()等函数的时候，请先了解一下什么叫字节序
//1 在写这段代码的同时，请各位参考我给大家的《3.0 UDP创建流程图.png》来书写


int main()
{
    struct sockaddr_in6 dest_addr;
    memset(&dest_addr,0,sizeof(dest_addr));
    dest_addr.sin6_family = AF_INET6;
    dest_addr.sin6_port = htons(8888);
//    dest_addr.sin_addr.s_addr = inet_addr("192.168.2.13");
    inet_pton(AF_INET6,"2001:da8:270:2018:f816:3eff:fe40:d788",&dest_addr.sin6_addr);
    int tmp = 0;
    char buf[1024] = {0};
    int addrLen = sizeof(struct sockaddr_in6);

    //1 创建socket文件
    int sockfd = socket(AF_INET6,SOCK_DGRAM,0);
    if(-1 == sockfd)
        perror("socket creat error! \n");

    //2 收/发
    while(1)
    {
        memset(buf,0,sizeof(buf));
        //发
        printf("pls input the words that you want to transform: ");
        scanf("%s",buf);
        while( getchar() != '\n' );

        tmp = sendto(sockfd,buf,strlen(buf),0,(struct sockaddr *)&dest_addr,addrLen);
        if(tmp<0)
        {
            perror("socket send error! \n");
        }
        else
        {
            printf("send success\n");
        }

    }
	
	close(sockfd);


    return 0;
}
