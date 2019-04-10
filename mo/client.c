#include	<time.h>
#include <sys/types.h>   /* See NOTES */
#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#define MAXLINE 1024

int main(int argc, char **argv)
{
	int					sockfd, n;
	struct sockaddr_in6	servaddr;
	char				recvline[MAXLINE + 1];

	if (argc != 2) {
    printf("usage: a.out <IPaddress>");
    exit(-1);
  }
		

	if ( (sockfd = socket(AF_INET6, SOCK_STREAM, 0)) < 0) {
    perror("socket failed!\n");
  }
  printf("socket");

	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin6_family = AF_INET6;
	servaddr.sin6_port   = htons(5670);	/* daytime server */
	if (inet_pton(AF_INET6, argv[1], &servaddr.sin6_addr) <= 0) {
    perror("inet_pton failed!\n");
  }

	if (connect(sockfd, (struct sockaddr *) &servaddr, sizeof(servaddr)) < 0) {
    perror("connect failed!\n");
  }
  printf("connect");

	while ( (n = read(sockfd, recvline, MAXLINE)) > 0) {
		recvline[n] = 0;	/* null terminate */
		if (fputs(recvline, stdout) == EOF) {
      perror("fputs failed!\n");
    }
	}
	if (n < 0)
perror("failed!\n");

	exit(0);
}
