#include <stdio.h>
int main(int argc, char **argv)
{   
    FILE *fp;
    int jump;
    double da[120][10] = {0} ;
    printf(" 输入文件名: ");
    int flag=1;
    char buff[1024]={0};
    fp=fopen("橙子0001.nos","r");     

    while(jump++<52) 
        fgets(buff,1024,fp);        //第53行了。

    for(int i = 0 ;i < 120 ; i++) {
        for(int j = 0 ;j < 10; j++) {
            fscanf(fp,"%lf",&da[i][j]);
            fseek(fp, 1L, SEEK_CUR);   /*fp指针从当前位置向后移动*/
        }
        fgets(buff,1024,fp);    //每行读10个数据，然后换行
    }
}

