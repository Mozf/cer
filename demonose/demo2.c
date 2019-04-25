#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "engine.h"
#include "matrix.h"
#include <sys/types.h>         
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h> 
#include <sys/stat.h>
#include <fcntl.h>
#include <arpa/inet.h>
#include <unistd.h>

#define  BUFSIZE 100
#define  ROWS    120
#define  COLUMNS 10

int main(int argc, char **argv) {

	//matlab==============================================================
	Engine *ep;
	char kind[5],buffer[BUFSIZE + 1];
	int flag =0;
	mxArray *tdata = NULL, *result = NULL;

	if (!(ep =engOpen("/work/matlab2016/bin/matlab"))) {
		printf("\nCan't start MATLAB engine!\n\n");
		return EXIT_FAILURE;
	}	
	engSetVisible(ep,false);


	/*/socket===============================================================
	int sockfd = socket(AF_INET6,SOCK_STREAM,0);
	struct sockaddr_in6 server_addr;
	char 	buff_2[1024 + 1];

	server_addr.sin6_family = AF_INET6;
	server_addr.sin6_port = htons(8088);
	if (inet_pton(AF_INET6,"2001:da8:270:2018:f816:3eff:fe40:d788", &server_addr.sin6_addr) < 0 ) { 
		perror("inet_pton err");
		return -1;
	}
	bind(sockfd,(struct sockaddr*)&server_addr,sizeof(server_addr));
	listen(sockfd,10);
	struct sockaddr_in6 peer_addr;
	socklen_t len = sizeof(peer_addr);
	*/


	//readfile120*10=====================================================
	FILE *fp;
	int jump;
	double data[120][10] = {0} ;
	char buff[1024]={0};
	fp=fopen("橙子0001.nos","r");     

	while(jump++<52) 
		fgets(buff,1024,fp);        //第53行了。

	for(int i = 0 ;i < 120 ; i++) {
		for(int j = 0 ;j < 10; j++) {
			fscanf(fp,"%lf",&data[i][j]);
			fseek(fp, 1L, SEEK_CUR);   
		}
		fgets(buff,1024,fp);    
	}
	



	/*/socket===================================================================
	int new_sockfd = accept(sockfd,(struct sockaddr *)&peer_addr,&len);
	if(new_sockfd < 0) {
			perror("accept err");
			exit(-1);
	}
	else {
		printf("new_sockfd = %d\n",new_sockfd);
		double recvmsg[ROWS][COLUMNS];
		memset(recvmsg,0,sizeof(recvmsg));
		char *pRecvmsg =(char *)&recvmsg[0][0];
		int res= recv(new_sockfd,pRecvmsg,sizeof(double)*(ROWS*COLUMNS),0);
		if(res < 0) {
			perror("recv err");
			return -1;
		}
		else
		{
			int i=0,j=0;
			for(i=0;i<ROWS;i++)
			{
				for(j=0;j<COLUMNS;j++)
				{
					printf(" %lf ",recvmsg[i][j]);
				}
				putchar('\n');
			}
		}
	}
	*/
	

	//matlab===================================================================
	tdata = mxCreateDoubleMatrix(10,120,mxREAL);
	memcpy(mxGetPr(tdata),recvmsg,sizeof(double)*120*10);

	if(flag != engPutVariable(ep, "load_data", tdata)) {
		printf("1\n");			
	}
	
	if(flag != engEvalString(ep, "save ('data.mat','load_data');"))	 {
		printf("2\n"); 
	}
	
	buffer[BUFSIZE] = '\0';
	engOutputBuffer(ep, buffer, BUFSIZE);	

	if(flag != engEvalString(ep, "test_190425")) {
		printf("3\n");
	}
	
	if ((result = engGetVariable(ep, "kind")) !=NULL) {			
	   for (int i = 0; i < 2; i++) {
		  kind[i] = buffer[i + 14];					//kinds:0x01,0x02,0x03
		}
		kind[2]='\0';
		printf("level:%s\n", kind);				
	}
	else
		printf("ff\n" );
	
	mxDestroyArray(tdata);					
	mxDestroyArray(result);						


	/*/socket=================================================================================
	memset(buff_2, 0, sizeof(buff_2));
	strcpy(buff_2, kind);
	if (len = send(new_sockfd, buff_2, sizeof(buff_2), 0) == -1) {
		perror("send failed!\n");
	}


  close(new_sockfd);
	*/
	engClose(ep);		

	return 0;
}


