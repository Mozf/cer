#include <stdio.h>
#include <string.h>
#include "engine.h"
#include "matrix.h"

#define  BUFSIZE 100

int main(int argc, char **argv) {
  Engine *ep;
	mxArray *testdata = NULL, *result = NULL;
  int flag =0;
  double data[3][3] = {
    {1,1,1},
    {0,1,1},
    {1,0,1}
  };
  double datab[3][3];
  double asd[3][3] = {
    {1,-1,0},
    {1,0,-1},
    {-1,1,1}
  };
  
  printf("输入矩阵为：\n");
  for(int i = 0; i < 3; i++){
    for(int j = 0; j < 3; j++){
      printf("%f\t",data[i][j]);
    }
    printf("\n");
  }

  printf("答案为：\n");
  for(int i = 0; i < 3; i++) {
    for(int j = 0; j < 3; j++) {
      printf("%f\t",asd[i][j]);
    }
    printf("\n");
  }

  if (!(ep =engOpen("/usr/local/MATLAB/R2016b/bin/matlab"))) {
		printf("\nCan't start MATLAB engine!\n\n");
		return EXIT_FAILURE;
	}	
	engSetVisible(ep,0);

  testdata = mxCreateDoubleMatrix(3,3,mxREAL);
  result = mxCreateDoubleMatrix(3,3,mxREAL);

  memcpy(mxGetPr(testdata),data,sizeof(double)*3*3);

  if(flag != engPutVariable(ep, "testdata", testdata)) {
		printf("f2ff\n");			
	}

  printf("进行逆变换：\n");
  if(flag != engEvalString(ep,"result = inv(testdata)")) {
    printf("f2ff\n");	
  }

  result = engGetVariable(ep,"result");
  memcpy(datab,mxGetPr(result),sizeof(datab));

  mxDestroyArray(testdata);
  mxDestroyArray(result);

  engClose(ep);

  printf("输出矩阵为：\n");
  for(int i = 0; i < 3; i++) {
    for(int j = 0; j < 3; j++) {
      printf("%f\t",datab[i][j]);
    }
    printf("\n");
  }
}