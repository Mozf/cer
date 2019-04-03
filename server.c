#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>          /* See NOTES */
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h> /* superset of previous */
#include <sys/stat.h>
#include <fcntl.h>
#include <netdb.h>
struct Data{
    int len;
    char buf[1024];
};

int main()
{
#ifdef R
    //1 创建socket
    int sockfd = socket(AF_INET6,SOCK_STREAM,0);
    //* bind
    struct sockaddr_in6 server_addr;
    server_addr.sin6_family = AF_INET6;
    server_addr.sin6_port = htons(8888);
    if (inet_pton(AF_INET6,"2409:8955:c98:4c9f:20c:29ff:fe07:3025", &server_addr.sin6_addr) < 0 ) 
    {                 // IPv6
        perror("inet_pton err");
        return -1;
    }

    //server_addr.sin6_addr.s6_addr = inet_addr("2001:da8:270:2018:f816:3eff:fe40:d788");
    bind(sockfd,(struct sockaddr*)&server_addr,sizeof(server_addr));
    //2 listen 让服务器socket进入监听状态（只有进入监听状态才能接受链接）
    //           参数二 表示 同时允许的最大的 正在链接 的客户端数量
#else
    struct sockaddr_in6 from;
    struct addrinfo req, *ans;
    int code,sockfd, len;
    req.ai_flags = AI_PASSIVE;     
    req.ai_family = PF_INET6;
    req.ai_socktype = SOCK_STREAM;
    req.ai_protocol = 0;
    if ((code = getaddrinfo("2001:da8:2018:1001:20c:29ff:fe07:3025", "8888", &req, &ans)) != 0) {
        fprintf(stderr, "rlogind: getaddrinfo failed code %d\n",
            code);
        exit(-1);
    }
    sockfd = socket(ans->ai_family, ans->ai_socktype, ans->ai_protocol);
    if (bind(sockfd, ans->ai_addr, ans->ai_addrlen) < 0) {
        perror("bind err");
        exit(-1);
    }
#endif
    listen(sockfd,10);
    //3 accept
    while(1)
    {
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
            //2 recv
            struct Data data;
            int res = recv(new_sockfd,&data,sizeof(data),0);
            if(res < 0)
            {
                perror("recv err");
                break;
            }
            else
            {
                //3 find local file
                //4 File IO
                char *filname = data.buf;
                printf("filename = %s\n",filname);
                int fd = open(filname,O_RDONLY,0);
                if(fd < 0)
                {
                    perror("file not fond");
                    break;
                }
                else
                {
                    //5 send 
                    while(1)
                    {
                        struct Data data_send;
                        int len = read(fd,data_send.buf,sizeof(data_send.buf),0);
                        data_send.len = len;
                        printf("len = %d\n",len);
                        if(len == 0)
                            break;
                        send(new_sockfd,&data_send,data_send.len + sizeof(data_send.len),0);
                    }
                }
                close(fd);

            }
        }
    }
    //
    //

    //4 close

#ifdef R
    close(sockfd);
#else
    freeaddrinfo(ans);
#endif
    return 0;
}
