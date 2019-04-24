#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "engine.h"
#include "matrix.h"
//
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>



#define  BUFSIZE 100

int main()
{

	Engine *ep;
	char level[5],buffer[BUFSIZE + 1];
	int i =0, j =0,flag =0;
	mxArray *testdata = NULL, *result = NULL;

	if (!(ep =engOpen("/work/matlab2016/bin/matlab")))
	{
		printf("\nCan't start MATLAB engine!\n\n");
		return EXIT_FAILURE;
	}	
	engSetVisible(ep,false);

	//服务器做数据截取，得气味数据120*2
	char data[]={"022936010229360102293601032936010229360102293601022836010328350103283500022734010227340102263301032633010325320003243101022431010223300103222F0103222E0103222E0102212D0102212D0102222C0103222C0002222C0102222C0102222C0102222C0103222C0102212B01"};

	//	data[240]='/0';
	testdata = mxCreateString(data); //mxCreateString创建一个1*N维的字符串阵列。

	if(flag != engPutVariable(ep, "input_data", testdata))			//检查发数据情况
	{
		printf("f2ff\n");			
	}

	if(flag != engEvalString(ep, "save ('data.mat','input_data');"))	//检查存数据情况
	{
		printf("f3ff\n"); 
	}

	buffer[BUFSIZE] = '\0';
	engOutputBuffer(ep, buffer, BUFSIZE);						
	if(flag != engEvalString(ep, "Mtest"))					 //检查算法文件执行
	{
		printf("f4ff\n");
	}

	if ((result = engGetVariable(ep, "level")) !=NULL)
	{
									
	//	   printf("the right buffer is  %s\n",buffer);
		for (i = 0; i < 2; i++)
		{
			level[i] = buffer[i + 14];					//kinds:0x01,0x02,0x03
			level[i+2] = buffer[i+30];					//levels:0x01,0x02,0x03,0x04,0x05
		}
		level[4]='\0';
		printf("level:%s\n", level);					//输出结果：第一字节是分类结果，第二字节是分级结果
	}else
			printf("ffff\n" );
	
	mxDestroyArray(testdata);					
	mxDestroyArray(result);										
	engClose(ep);		
	return EXIT_SUCCESS;
}


