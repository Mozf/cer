#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "engine.h"
#include "matrix.h"

#define  BUFSIZE 100

int main(int argc, char **argv) {
 
	Engine *ep;
	char level[5],buffer[BUFSIZE + 1];
	int flag =0;
	mxArray *testdata = NULL, *result = NULL;

	if (!(ep =engOpen("/usr/local/MATLAB/R2016b/bin/matlab"))) {
		printf("\nCan't start MATLAB engine!\n\n");
		return EXIT_FAILURE;
	}	
	engSetVisible(ep,false);

	//readfile120*10=====================================================
	FILE *fp;
	int jump;
	double data[120][10] = {0} ;
	printf(" 输入文件名: ");
	int flag=1;
	char buff[1024]={0};
	fp=fopen("橙子0001.nos","r");     

	while(jump++<52) 
		fgets(buff,1024,fp);        //第53行了。

	for(int i = 0 ;i < 120 ; i++) {
		for(int j = 0 ;j < 10; j++) {
			fscanf(fp,"%lf",&data[i][j]);
			fseek(fp, 1L, SEEK_CUR);   /*fp指针从当前位置向后移动*/
		}
		fgets(buff,1024,fp);    //每行读10个数据，然后换行
	}
	
	testdata = mxCreateDoubleMatrix(3,3,mxREAL);
	memcpy(mxGetPr(testdata),data,sizeof(double)*3*3);

	if(flag != engPutVariable(ep, "load_data", testdata))			//检查发数据情况
	{
		printf("f2ff\n");			
	}
	
	if(flag != engEvalString(ep, "save ('data.mat','load_data');"))	//检查存数据情况
	{
		printf("f3ff\n"); 
	}
	
	buffer[BUFSIZE] = '\0';
	engOutputBuffer(ep, buffer, BUFSIZE);						
	if(flag != engEvalString(ep, "test_190425"))					 //检查算法文件执行
	{
		printf("f4ff\n");
	}
	
	if ((result = engGetVariable(ep, "level")) !=NULL)
	{
									
	//	   printf("the right buffer is  %s\n",buffer);
	   for (int i = 0; i < 2; i++)
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


