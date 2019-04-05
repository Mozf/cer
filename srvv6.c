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
	int					listenfd, connfd;
	socklen_t			len;
	char				buff[MAXLINE];
	time_t				ticks;
	struct sockaddr_in6	servaddr, cliaddr;

	listenfd = socket(AF_INET6, SOCK_STREAM, 0);
  if (listenfd == -1) {
    perror("socket failed!\n");
  }

	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin6_family = AF_INET6;
	servaddr.sin6_addr   = in6addr_any;
	servaddr.sin6_port   = htons(13);	/* daytime server */

	if (bind(listenfd, (struct sockaddr *) &servaddr, sizeof(servaddr)) == -1) {
    perror("failed!\n");
  }

	if (listen(listenfd, 5) == -1) {
    perror("failed!\n");
  }

	for ( ; ; ) {
		len = sizeof(cliaddr);
		connfd = accept(listenfd, (struct sockaddr *) &cliaddr, &len);
    if (connfd == -1) {
      perror("accept failed!\n");
    }
	//	printf("connection from %s\n",
	//	sock_ntop((struct sockaddr *) &cliaddr, len));

        ticks = time(NULL);
        snprintf(buff, sizeof(buff), "%.24s\r\n", ctime(&ticks));
        write(connfd, buff, strlen(buff));

		close(connfd);
	}
}
