#include <sys/types.h>   /* See NOTES */
#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#include <errno.h>
#include <resolv.h>

#define MAXLINE 1024

int main(int argc, char **argv)
{
	int					sockfd, n;
	struct sockaddr_in6	servaddr;
	char				recvline[MAXLINE + 1];

	//if (argc != 2) {
   // printf("usage: a.out <IPaddress>");
  //  exit(-1);
  //}
		

	if ( (sockfd = socket(AF_INET6, SOCK_STREAM, 0)) < 0) {
    perror("socket failed!\n");
  }

	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin6_family = AF_INET6;
	servaddr.sin6_port   = htons(5670);	/* daytime server */
	if (inet_pton(AF_INET6,"2001:da8:270:2018:f816:3eff:fe40:d788", &servaddr.sin6_addr) <= 0) {
    perror("inet_pton failed!\n");
  }

	if (connect(sockfd, (struct sockaddr *) &servaddr, sizeof(servaddr)) < 0) {
    perror("connect failed!\n");
  }

	char				buff[MAXLINE];
/*	bzero(buff,1025);
	n = recv(sockfd,buff,MAXLINE,0);
	if(n>0)	printf("%s",buff);
	else printf("errno");
*/
	bzero(buff,1025);
	strcpy(buff,"qqcl\n");
	n=send(sockfd,buff,strlen(buff),0);
	if(n<0) printf("errno");
	else printf("%s",buff);

	//bzero(buff,1025);
  //n = recv(sockfd,buff,MAXLINE,0);
  //if(n>0) printf("%s",buff);
  //else printf("errno");

	close(sockfd);
	//snprintf(buff, sizeof(buff), "%.24s\r\n","qqqqq");
	//write(sockfd, buff, strlen(buff));
	/*printf("123");
	while ( (n = read(sockfd, recvline, MAXLINE)) > 0) {
		recvline[n] = 0;	 null terminate 
		if (fputs(recvline, stdout) == EOF) {
      perror("fputs failed!\n");
    }
		exit(0);
	}
	snprintf(buff, sizeof(buff), "%.24s\r\n","qqqqq");
 write(sockfd, buff, strlen(buff));
	if (n < 0)
		perror("failed!\n");*/
//
	
}
