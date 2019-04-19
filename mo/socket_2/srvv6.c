#include	<time.h>
#include <sys/types.h>   
#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>

#define MAXLINE 1024

int main(int argc, char **argv){

	int	        listenfd, connfd;
	char 				buff[MAXLINE + 1];
	time_t			ticks;
	socklen_t		len;
	
	struct sockaddr_in6	servaddr, cliaddr;

  if (listenfd = socket(AF_INET6, SOCK_STREAM, 0) == -1) {
    perror("socket failed!\n");
		exit(1);
  }
	else {
		printf("socket created\n");
	}

	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin6_family = AF_INET6;
	servaddr.sin6_addr   = in6addr_any;
	servaddr.sin6_port   = htons(5670);	

	if (bind(listenfd, (struct sockaddr *) &servaddr, sizeof(servaddr)) == -1) {
    perror("bind failed!\n");
		exit(1);
  }
	else {
		printf("binded\n");
	}

	if (listen(listenfd, 5) == -1) {
    perror("listen failed!\n");
		exit(1);
  }
	else {
		printf("begin listen\n");
	}
	
	for ( ; ; ) {

		len = sizeof(cliaddr);

    if (connfd = accept(listenfd, (struct sockaddr *) &cliaddr, &len) == -1) {
      perror("accept failed!\n");
			exit(1);
    }
		else {
			printf("accept\n");
		}

    bzero(buff,MAXLINE + 1);
    if(len = recv(connfd,buff,strlen(buff),MSG_WAITALL) == -1) {
			perror("recv failed!\n");
		}
		else {
			printf("%s\n",buff);
		}

		bzero(buff,MAXLINE + 1);
		strcpy(buff, "这是server发给client的消息\n");
    if (len = send(connfd, buff, strlen(buff), 0) == -1) {
			perror("send failed!\n");
		}
		else {
			printf("send\n");
		}

	  close(connfd);
		return 0;
	}
}
