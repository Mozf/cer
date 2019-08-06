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
#include <arpa/inet.h>
#include <string.h>

#define ROWS 120
#define COLUMNS 10
void readfile(double da[ROWS][COLUMNS],char *path)
{
    memset(da,0,sizeof(double)*(ROWS*COLUMNS));
    FILE *fp;
//    char filename[40]  ;
    int i = 0,j = 0 ;
//    printf(" 输入文件名: ");
    int flag=1;
    char buff[1024]={0};
//  gets(filename);
    
    fp=fopen(path,"r");     // fp指针指向文件头部
    if(fp==NULL)
    {
        perror("fopen err :");
        exit(-1);
    }
    while(i++<52)
    {
        fgets(buff,1024,fp);        //文件流指针到54行，从文件第54行开始读
    }
    for(i = 0 ;i < ROWS ; i++)
    {
        for(j = 0 ;j < COLUMNS; j++)
        {
            fscanf(fp,"%lf",&da[i][j]);
            fseek(fp, 1L, SEEK_CUR);   /*fp指针从当前位置向后移动*/
        }
        fgets(buff,1024,fp);    //每行读10个数据，然后换行
    }
//打印.nos文件读取的结果
/*
    for(i = 0 ;i < ROWS ; i++)
    {
        for(j=0;j< COLUMNS;j++)
        {
            printf(" %lf ",da[i][j]);
        }
        putchar('\n');
    }
    printf("===========================================\n");
*/
}
void show_result(char *result)
{
    char str_01[]={"01"};
    char str_02[]={"02"};
    char str_03[]={"03"};
    char str_04[]={"04"};
    if(strcmp(str_01,result)==0)
        printf("该气味是：哈密瓜\n");
    else if(strcmp(str_02,result)==0)
        printf("该气味是：火龙果\n");
    else if(strcmp(str_03,result)==0)
        printf("该气味是：苹果\n");
    else if(strcmp(str_04,result)==0)
        printf("该气味是：香蕉\n");
    else
    {
        printf("识别失败\n");
    }
}
int main(int argc, const char *argv[])
{
    if(argc < 2)
    {
        printf("usge ./client path\n");
        exit(-1);
    }
    int sockfd = socket(AF_INET6,SOCK_STREAM,0);
    if(sockfd<0)
    {
        perror("socket err:");
    }
//    printf("sockfd:%d\n",sockfd);
    struct sockaddr_in6 server_addr;
    server_addr.sin6_family = AF_INET6;
    server_addr.sin6_port = htons(8088);
    if (inet_pton(AF_INET6,"2001:da8:270:2018:f816:3eff:fe40:d788", &server_addr.sin6_addr) < 0 ) 
    {                 // IPv6
        perror("inet_pton err");
        return -1;
    }
    if(connect(sockfd,(struct sockaddr *)&server_addr,sizeof(server_addr))<0)
    {
        perror("connect err");
        return -1;
    }
    double msg[ROWS][COLUMNS]={0};
    readfile(msg,argv[1]);
    char* pmsg =(char*)&msg[0][0];
    int res = send(sockfd,pmsg,sizeof(double)*(ROWS*COLUMNS),0);
    if(res < 0)
    {
        perror("send err :");
        return -1;
    }
    else 
    {
  //      printf("send size : %d\n",res);
  //      printf("send success\n");
    }
    //接受返回的结果

    char buf[1024]={0};
    res=recv(sockfd,buf,sizeof(buf),0);
    if(res < 0)
    {
        perror("recv err:");
        return -1;
    }
    else
    {
       // printf("result : %s\n",buf);
        show_result(buf);
       // printf("recv success\n");
    }

    close(sockfd);
    return 0;
}
