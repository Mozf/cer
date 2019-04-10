#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/wait.h>
#include <unistd.h>
#include <arpa/inet.h>
 
int main(int argc, char **argv)
{
	struct sockaddr_in6 s_addr;
	int sock;
	int addr_len;
	int len;
	char buff[128];
 
	if ((sock = socket(AF_INET6, SOCK_DGRAM, 0)) == -1) {
		perror("socket");
		exit(errno);
	} else
		printf("create socket.\n\r");
 
	s_addr.sin6_family = AF_INET6;
	s_addr.sin6_port = htons(5683);
 
	inet_pton(AF_INET6, 2001:da8:270:2018:f816:3eff:fe40:d788, &s_addr.sin6_addr);
 
	addr_len = sizeof(s_addr);
	strcpy(buff, "hello i'm here");
	len = sendto(sock, buff, strlen(buff), 0,(struct sockaddr *) &s_addr, addr_len);
	if (len < 0) {
		printf("\n\rsend error.\n\r");
		return 3;
	}
 
	printf("send success.\n\r");
	return 0;
}
