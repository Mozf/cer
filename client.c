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
    if(argc < 2)
    {
        printf("Usage: ./a.out fileName\n");
        exit(-1);
    }
    //目的： ./a.out /home/ubuntu/test.txt
    //服务器就会返回该文件的内容给我们
    //我们在接受到文件之后就将数据保存为 /home/ubuntu/test.txt

    //1 创建socket
    int sockfd = socket(AF_INET6,SOCK_STREAM,0);
    if(sockfd<0)
    {
    	perror("socket err:");
    }
    printf("sockfd:%d\n",sockfd);
    //2 向服务器请求链接
    struct sockaddr_in6 server_addr;
    server_addr.sin6_family = AF_INET6;
<<<<<<< HEAD
    server_addr.sin6_port = htons(8888);
    if (inet_pton(AF_INET6,"2409:8955:ce0:3a14:20c:29ff:fe07:3025", &server_addr.sin6_addr) < 0 ) 
=======
    server_addr.sin6_port = htons(5670);
    if (inet_pton(AF_INET6,"2001:da8:270:2018:f816:3eff:fe40:d788", &server_addr.sin6_addr) < 0 ) 
>>>>>>> 4df8953d75a9fcd985ebfdb50e819391f5477cbf
    {                 // IPv6
        perror("inet_pton err");
        return -1;
    }
    printf("===========\n");
    //server_addr.sin6_addr.__in6_u.__u6_addr32 = inet_addr("2001:da8:270:2018:f816:3eff:fe40:d788");
    //server_addr.sin6_addr = in6addr_any;
    if(connect(sockfd,(struct sockaddr *)&server_addr,sizeof(server_addr))<0)
    {
    	perror("connect err");
        return -1;
    }
    printf("123\n");
    //2 send 请求数据
    struct Data data;
    struct Data cli_to_ser;
    memset(&data, 0, sizeof(data));  
    memset(&cli_to_ser, 0, sizeof(data));
    
    int fd_clitoser = open("cli_to_ser.txt",O_RDONLY | O_CREAT,777);
    if(fd_clitoser<0)
    {
        perror("fd_clitoser err:");
        return -1;
    }
    printf("fd_clitoser is %d\n",fd_clitoser);
    int read_len=read(fd_clitoser,cli_to_ser.buf,sizeof(cli_to_ser.buf));
    if(read_len<0)
    {
        perror("read err:");
        return -1;
    }
    else
    {
        printf("read file cli_to_ser.txt len is %d\n",read_len);
    }
    cli_to_ser.len=strlen(cli_to_ser.buf);
    printf("cli_to_ser.len is %d\n",cli_to_ser.len);
    int res_sendfiletoser=send(sockfd,&cli_to_ser,sizeof(cli_to_ser),0);
    if(res_sendfiletoser<0)
    {
        perror("send file to ser err:");
        return -1;
    }
    else
    {
        printf("send file to server is successful!!!!!!\n");
        printf("=========================================\n");
    }
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

    close(fd);
    close(sockfd);

    return 0;
}
