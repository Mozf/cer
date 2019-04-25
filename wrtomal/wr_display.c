#include <stdio.h>
#include <string.h>
#include "engine.h"
#include "matrix.h"

#define  BUFSIZE 100

int main(int argc, char **argv) {
  Engine *ep;
	mxArray *testdata = NULL;
  int flag =0;
  double data[3][4] = {
    {1,2,3,4},
    {5,6,7,8},
    {9,10,11,12}
  };
  
  printf("输入矩阵为：\n");
  for(int i = 0; i < 3; i++){
    for(int j = 0; j < 4; j++){
      printf("%f\t",data[i][j]);
    }
    printf("\n");
  }

  if (!(ep =engOpen("/usr/local/MATLAB/R2016b/bin/matlab"))) {
		printf("\nCan't start MATLAB engine!\n\n");
		return EXIT_FAILURE;
	}	
	engSetVisible(ep,0);

  testdata = mxCreateDoubleMatrix(4,3,mxREAL);

  memcpy(mxGetPr(testdata),data,sizeof(double)*3*4);

  if(flag != engPutVariable(ep, "testdata", testdata)) {
		printf("f2ff\n");			
	}

  //检查存数据情况
  if(flag != engEvalString(ep, "save ('data.mat','testdata');")) {
		printf("f3ff\n"); 
	}

  mxDestroyArray(testdata);

  engClose(ep);
}