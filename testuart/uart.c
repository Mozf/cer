#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <errno.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <termios.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0

int speed_arr[] = { B115200, B38400, B19200, B9600, B4800, B2400, B1200, B300, B38400, B19200, B9600, B4800, B2400, B1200, B300, };
int name_arr[] = {115200, 38400,  19200,  9600,  4800,  2400,  1200,  300, 38400,  19200,  9600, 4800, 2400, 1200,  300, };

int Opendev(char * Dev)//打开串口设备文件
{
  int fd = open(Dev, O_RDWR | O_NOCTTY);
  if(fd < 0)
  {
    perror("can not open serial\n");
    return -1;
  }
  else
  {
    printf("open com success\n");
    return fd;
  }
}

void set_speed(int fd, int speed)//设置波特率
{
  int i;
  int status;
  struct termios Opt;
  tcgetattr(fd, &Opt);
  for ( i = 0; i < sizeof(speed_arr) / sizeof(int); i++)
  { 
    if (speed == name_arr[i]) 
    { 
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
//设置数据位，停止位，校验位
int set_Parity(int fd, int databits, int stopbits, int parity) 
{ 
  struct termios options; 
  if ( tcgetattr( fd,&options) != 0) 
  {
    perror("SetupSerial 1");
    return(FALSE);
  } 
  bzero(&options,sizeof(options)); 
  options.c_cflag |= CLOCAL | CREAD;
  options.c_cflag &= ~CSIZE; 
  switch (databits) 
  { 
    case 7: 
      options.c_cflag |= CS7;
      break;
    case 8:
      options.c_cflag |= CS8;
      break; 
    default: fprintf(stderr,"Unsupported data size\n");
    return (FALSE); 
  } 
  switch (parity) 
  {
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
  switch (stopbits)
  { 
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
  if (tcsetattr(fd,TCSANOW,&options) != 0)
  {  
    perror("SetupSerial 3"); 
    return (FALSE);
  } 
  return (TRUE);
}

int printfread (char *buff)
{
  int i;
  char *p;
  p = buff;
  for(i = 0; i < 255; i++)
  {
      printf("%c", p[i]);
  }
  putchar('\n');
  return 0;
}

int main(int argc, char **argv)
{
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
  while(1){
    memset(recvbuffer, 0, sizeof(recvbuffer));
    memset(sendbuffer, 0, sizeof(sendbuffer));

    printf("nread is %d\n", nread);
    while((nread = read(fd, recvbuffer, sizeof(recvbuffer))) == 0);
    if((nread > 0)) {       
      printf("recv Success!\n"); 
    }

    printfread(recvbuffer);

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
  };
}  
