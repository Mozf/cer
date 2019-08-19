#include <stdio.h>
#include <sys/types.h>          
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h> 
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <errno.h>
#include <termios.h>

//client===========================================================
#define ROWS 120
#define COLUMNS 10

//uart=============================================================
#define TRUE 1
#define FALSE 0

int speed_arr[] = {B115200, B38400, B19200, B9600, B4800, B2400, B1200, B300, B38400, B19200, B9600, B4800, B2400, B1200, B300, };
int name_arr[] = {115200, 38400,  19200,  9600,  4800,  2400,  1200,  300, 38400,  19200,  9600, 4800, 2400, 1200,  300, };

//client===========================================================
void readfile(double da[ROWS][COLUMNS], char *path)
{
  memset(da, 0, sizeof(double)*(ROWS*COLUMNS));
  FILE *fp;
  int i = 0,j = 0 ;
  int flag = 1;
  char buff[1024] = {0};
  fp = fopen(path,"r");     // fp指针指向文件头部
  if(fp == NULL)
  {
    perror("fopen err :");
    exit(-1);
  }
  while(i ++< 52)
  {
    fgets(buff, 1024, fp);     //文件流指针到54行，从文件第54行开始读
  }
  for(i = 0; i < ROWS; i++)
  {
    for(j = 0; j < COLUMNS; j++)
    {
      fscanf(fp, "%lf", &da[i][j]);
      fseek(fp, 1L, SEEK_CUR);   /*fp指针从当前位置向后移动*/
    }
    fgets(buff, 1024, fp);    //每行读10个数据，然后换行
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
  char str_01[] = {"01"};
  char str_02[] = {"02"};
  char str_03[] = {"03"};
  char str_04[] = {"04"};
  if(strcmp(str_01,result) == 0)
    printf("该气味是：哈密瓜\n");
  else if(strcmp(str_02,result) == 0)
    printf("该气味是：火龙果\n");
  else if(strcmp(str_03,result) == 0)
    printf("该气味是：苹果\n");
  else if(strcmp(str_04,result) == 0)
    printf("该气味是：香蕉\n");
  else
  {
    printf("识别失败\n");
  }
}

//uart=============================================================
int Opendev(char * Dev) {
  int fd = open(Dev, O_RDWR | O_NOCTTY);
  if(fd < 0) {
    perror("can not open serial\n");
    return -1;
  }
  else {
    printf("open com success\n");
    return fd;
  }
}

void set_speed(int fd, int speed) {
  int i;
  int status;
  struct termios Opt;
  tcgetattr(fd, &Opt);
  for ( i = 0; i < sizeof(speed_arr) / sizeof(int); i++) { 
    if (speed == name_arr[i]) { 
      tcflush(fd, TCIOFLUSH); 
      cfsetispeed(&Opt, speed_arr[i]);
      cfsetospeed(&Opt, speed_arr[i]);
      status = tcsetattr(fd, TCSANOW, &Opt); 
      if (status != 0) perror("tcsetattr fd1");
      return;
    } 
    tcflush(fd, TCIOFLUSH);
  }
}

int set_Parity(int fd, int databits, int stopbits, int parity) { 
  struct termios options; 
  
  if ( tcgetattr( fd,&options) != 0) {
    perror("SetupSerial 1");
    return(FALSE);
  } 
  
  bzero(&options,sizeof(options)); 
  options.c_cflag |= CLOCAL | CREAD;
  options.c_cflag &= ~CSIZE; 
  
  switch (databits) { 
    case 7: 
      options.c_cflag |= CS7;
      break;
    case 8:
      options.c_cflag |= CS8;
      break; 
    default: fprintf(stderr,"Unsupported data size\n");
    return (FALSE); 
  } 

  switch (parity) {
    case 'n': 
    case 'N':
      options.c_cflag &= ~PARENB;
      options.c_cflag &= ~INPCK; 
      break; 
    case 'o':
    case 'O': 
      options.c_cflag |= (PARODD | PARENB);
      options.c_cflag |= (INPCK | ISTRIP); 
      break; 
    case 'e': 
    case 'E': 
      options.c_cflag |= PARENB;
      options.c_cflag &= ~PARODD; 
      options.c_cflag |= (INPCK | ISTRIP); 
      break; 
    case 'S': 
    case 's': 
      options.c_cflag &= ~PARENB; 
      options.c_cflag &= ~CSTOPB;
      break;
    default: fprintf(stderr,"Unsupported parity\n"); 
    return (FALSE); 
  } 

  switch (stopbits) { 
    case 1:
      options.c_cflag &= ~CSTOPB; 
      break; 
    case 2: 
      options.c_cflag |= CSTOPB;
      break; 
    default: fprintf(stderr,"Unsupported stop bits\n"); 
    return (FALSE); 
  } 
  if (parity != 'n') 
    options.c_cflag |= INPCK; 
  
  options.c_cc[VTIME] = 0;
 
  options.c_cc[VMIN] = 0;
  
  tcflush(fd,TCIFLUSH); 
  
  if (tcsetattr(fd,TCSANOW,&options) != 0) {  
    perror("SetupSerial 3"); 
    return (FALSE);
  } 
  return (TRUE);
}

int printfread (char *buff) {
  int i;
  char *p;
  p = buff;

  for(i = 0; i < 255; i++) {
    printf("%c", p[i]);
  }
  putchar('\n');

  return 0;
}

int main(int argc, char **argv) {
  //client====================================================================
  int sockfd = socket(AF_INET6, SOCK_STREAM, 0);
  if(sockfd<0) {
    perror("socket err:");
  }
  //    printf("sockfd:%d\n",sockfd);
  struct sockaddr_in6 server_addr;
  server_addr.sin6_family = AF_INET6;
  server_addr.sin6_port = htons(8088);
  if(inet_pton(AF_INET6, "2001:da8:270:2018:f816:3eff:fe40:d788", &server_addr.sin6_addr) < 0 ) {                 // IPv6
    perror("inet_pton err");
    return -1;
  }

  //uart=====================================================================
  int fd;
  int nread = -1;
  int nwrite = -1;
  char recvbuffer[255];
  char sendbuffer[255];
  char *send1 = "q";
  char *sendd = "d";
  char *sendg = "g";

  char *dev_name = "/dev/ttyUSB1";//根据实际情况选择串口
  while(1) {  
    fd = Opendev(dev_name); //打开串口 
    if(fd > 0) 
      set_speed(fd, 115200); //设置波特率 
    else { 
      printf("Can't Open Serial Port!\n"); 
      sleep(1);
      continue; 
    } 
    break;
  }

  if(set_Parity(fd, 8, 1, 'N') == FALSE) {
    printf("Set Parity Error\n"); 
    exit(1);
  }

  sleep(1); 

  //1. 接收到zynq发过来的信息，如果是running则继续下面程序；
  //2. 当服务器返回数据时，则发‘g’给zynq后，显示接收到的返回信息；
  while(1) {
    //uart==============================================================
    sleep(1); 
    memset(recvbuffer, 0, sizeof(recvbuffer));
    memset(sendbuffer, 0, sizeof(sendbuffer));

    printf("nread is %d\n", nread);
    while((nread = read(fd, recvbuffer, sizeof(recvbuffer))) == 0);
    if((nread > 0)) {       
      printf("recv Success!\n"); 
    }
    printfread(recvbuffer);

    //client============================================================
    if(connect(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr))<0) {
      perror("connect err");
      return -1;
    }

    double msg[ROWS][COLUMNS] = {0};
    readfile(msg, argv[1]);
    char* pmsg = (char*)&msg[0][0];
    int res = send(sockfd, pmsg, sizeof(double)*(ROWS*COLUMNS), 0);

    if(res < 0) {
      perror("send err :");
      return -1;
    }
    else {
    //printf("send size : %d\n",res);
    //printf("send success\n");
    }
    //接受返回的结果

    char buf[1024] = {0};
    res=recv(sockfd, buf, sizeof(buf), 0);
    if(res < 0) {
      perror("recv err:");
      return -1;
    }
    else {
      // printf("result : %s\n",buf);
      show_result(buf);
      // printf("recv success\n");
    }

    close(sockfd);

    //uart=============================================================
    printf("\n1\n");
    for(int i = 0; i < strlen(send1); i++) {
      sendbuffer[i] = send1[i];
    }
    printfread(sendbuffer);
    nwrite = write(fd, sendbuffer, 1);
    if((nwrite > 0)){
      printf("send success!\n");
    }
    memset(sendbuffer, 0, sizeof(sendbuffer));

    printf("\n2\n");
    for(int i = 0; i < strlen(sendd); i++) {
      sendbuffer[i] = sendd[i];
    }
    printfread(sendbuffer);
    nwrite = write(fd, sendbuffer, 1);
    if((nwrite > 0)){
      printf("send success!\n");
    }
    memset(sendbuffer, 0, sizeof(sendbuffer));

    printf("\n3\n");
    for(int i = 0; i < strlen(sendg); i++) {
      sendbuffer[i] = sendg[i];
    }
    printfread(sendbuffer);
    nwrite = write(fd, sendbuffer, 1);
    if((nwrite > 0)){
      printf("send success!\n");
    }
    memset(sendbuffer, 0, sizeof(sendbuffer));

    memset(recvbuffer, 0, sizeof(recvbuffer));
    while((nread = read(fd, recvbuffer, sizeof(recvbuffer))) == 0);

    nread = read(fd, recvbuffer, sizeof(recvbuffer));
    if((nread > 0)) {       
      printf("recv Success!\n"); 
    }

    printfread(recvbuffer);
  }
  
  return 0;
}
