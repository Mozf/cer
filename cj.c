#include <stdio.h>
#include <string.h>
int fun(char const * ptr,int j)
{
    if(j>50) 
    {
        return 0;
    }
   int i;
    i=0;
    while(i<j)
    {
        printf("%c\n",ptr[j]);
        if(ptr[i]!=ptr[j])
        {
            return 0;
        }
        i++;
        j--;
    }
    return 1;
}

int main(int argc, char const *argv[])
{
    char ch[50];
    printf("please input character\n");
    scanf("%s",ch);
    int len;
    len=strlen(ch)-1;
    printf("%d\n",fun(ch,len));
    return 0;
}