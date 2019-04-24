#include <stdio.h>
int main(void)
{   
    FILE *fp;
    char filename[40]  ;
    int i,j ;
    double da[6][10] = {0} ;
    printf(" 输入文件名: ");
    int flag=1;
    char buff[1024]={0};
    gets(filename);
    fp=fopen(filename,"r");     // fp指针指向文件头部
    while(i++<52) 
    fgets(buff,1024,fp);        //第53行了。
    for(i = 0 ;i < 6 ; i++)
    {
        for(j = 0 ;j < 10; j++)
        {
            fscanf(fp,"%lf",&da[i][j]);
            fseek(fp, 1L, SEEK_CUR);   /*fp指针从当前位置向后移动*/
        }
        fgets(buff,1024,fp);    //每行读10个数据，然后换行
    }
    for(i = 0 ;i < 6 ; i++)
    {
        for(j=0;j<10;j++)
        {
            printf(" %lf ",da[i][j]);
        }
        putchar('\n');
    }
}

