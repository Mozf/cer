#include <sys/types.h>   
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
	int			sockfd, n;
	char		buff_1[MAXLINE + 1], buff_2[MAXLINE + 1];

	struct sockaddr_in6	servaddr;
	
	if ( (sockfd = socket(AF_INET6, SOCK_STREAM, 0)) < 0) {
    perror("socket failed!\n");
		exit(1);
  }
	else {
		printf("socket created\n");
	}

	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin6_family = AF_INET6;
	servaddr.sin6_port   = htons(5670);	

	if (inet_pton(AF_INET6,"2001:da8:270:2018:f816:3eff:fe40:d788", &servaddr.sin6_addr) <= 0) {
    perror("inet_pton failed!\n");
		exit(1);
  }
	else {
		printf("inet_pton success\n");
	}

	if (connect(sockfd, (struct sockaddr *) &servaddr, sizeof(servaddr)) < 0) {
    perror("connect failed!\n");
		exit(1);
  }
	else {
			printf("connect\n");
		}

	memset(buff_1, 0, sizeof(buff_1));
	strcpy(buff_1, "这是client发给server的消息2\n");
	if( n = send(sockfd,buff_1,sizeof(buff_1),0) < 0) {
		perror("connect failed!\n");
	}
	else printf("send already\n");

	if(n = recv(sockfd,buff_2,sizeof(buff_2),0) == -1) {
		perror("recv failed!\n");
	}
	else {
		printf("%s\n",buff_2);
	}

	close(sockfd);
	return 0;
}
