#include <stdio.h>
#include <sys/types.h>          /* See NOTES */
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h> /* superset of previous */
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>

struct Data{
    int len;
    char buf[1024];
};

int writeFile(int fd,struct Data *data_recv)
{

    //4.2写文件
    int res = write(fd,data_recv->buf,data_recv->len);
    if(res < 0)
    {
        perror("file write  err");
        return -1;
    }
    printf("write buf = %s\n",data_recv->buf);
}

int main(int argc,const char * argv[])
{
#ifdef R
    if(argc < 2)
    {
        printf("Usage: ./a.out fileName\n");
        exit(-1);
    }
    //目的： ./a.out /home/ubuntu/test.txt
    //服务器就会返回该文件的内容给我们
    //我们在接受到文件之后就将数据保存为 /home/ubuntu/test.txt

    //1 创建socket   
    printf("rui\n");
    int sockfd = socket(AF_INET6,SOCK_STREAM,0);
    if(sockfd<0)
    {
    	perror("socket err:");
    }
    printf("sockfd:%d\n",sockfd);
    //2 向服务器请求链接
    struct sockaddr_in6 server_addr;
    server_addr.sin6_family = AF_INET6;
    server_addr.sin6_port = htons(8888);
    if (inet_pton(AF_INET6,"2409:8955:c98:4c9f:20c:29ff:fe07:3025", &server_addr.sin6_addr) < 0 ) 
    {                 // IPv6
        perror("inet_pton err");
        return -1;
    }
#else
    if(argc < 2)
    {
        printf("Usage: ./a.out fileName\n");
        exit(-1);
    }
    struct addrinfo req, *ans;
    int code, sockfd;
    req.ai_family = PF_INET6;               /* Same as AF_INET6.            */
    req.ai_socktype = SOCK_STREAM;
    req.ai_protocol = 0;
    printf("0\n");
    if ((code = getaddrinfo("2001:da8:270:2018:f816:3eff:fe40:d788", "5670", &req, &ans)) != 0) {
        fprintf(stderr, "rlogin: getaddrinfo failed code %d\n",
            code);
        return -1;
    }
    printf("1\n");
    sockfd = socket(ans->ai_family, ans->ai_socktype, ans->ai_protocol);
    printf("2\n");
    if (sockfd < 0) {
        perror("rlogin: socket");
        exit(-1);
    }
    if (connect (sockfd, ans->ai_addr, ans->ai_addrlen) < 0) {
        perror("rlogin: connect");
        exit(-1);
    }
    printf("3\n");
#endif
    printf("===========\n");
    //server_addr.sin6_addr.__in6_u.__u6_addr32 = inet_addr("2001:da8:270:2018:f816:3eff:fe40:d788");
    //server_addr.sin6_addr = in6addr_any;
#ifdef R
    if(connect(sockfd,(struct sockaddr *)&server_addr,sizeof(server_addr))<0)
    {
    	perror("connect err");
    }
#else
    printf("123\n");
    //2 send 请求数据
    struct Data data;
    memset(&data, 0, sizeof(data));
    strcpy(data.buf,argv[1]);
    data.len = strlen(data.buf);
    //int res = send(sockfd,&data, data.len + sizeof(data.len) ,0);
    int res = send(sockfd, &data, sizeof(data), 0);
    if(res < 0)
    {
        perror("send err");
        return -1;
    }

    //4.1打开文件
    int fd  = open("test.txt",O_WRONLY | O_CREAT,777);
    printf("fileName = %s\n",argv[1]);
    if(fd < 0)
    {
        perror("file open  err");
        return -1;
    }

    while(1)
    {
        //3 recv 接受数据
        struct Data data_recv;
        memset(&data_recv, 0, sizeof(data_recv));
        res = recv(sockfd,&data_recv,sizeof(data_recv),0);
        printf("recv res = %d\n",res);
        static int i = 0;//这里用来表示 第几个包 
        i++;
        //如果是第一个包 并且 大小小于1024 那说明文件本身就很小，立刻返回
            //4 把接受到的数据 写入到文件中
        if(i == 1 && res < sizeof(data_recv.buf) )
        {
            //说明文件已经发送完毕
            writeFile(fd,&data_recv);
            break;
        }
        else if(res == sizeof(data_recv.buf) + sizeof(data_recv.len))
        {
            writeFile(fd,&data_recv);
            continue;
        }
        else if(res < sizeof(data_recv.buf))
        {
            //说明文件已经发送完毕
            writeFile(fd,&data_recv);
            break;
        }
    }
#endif
#ifdef R
    close(fd);
    close(sockfd);
#else
    freeaddrinfo(ans);
#endif
    return 0;
}
