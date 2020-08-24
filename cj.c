#include <stdio.h>
#include <string.h>
#define MAXN 20

bool palindrome( char *s )
{
    bool b = true; 
    char *p;
    p = s;
    p = s + strlen(s) - 1;
    while(s < p )
    {
        if(*p != *s)
        {
            b = false;
            break;
        }
        p--;
        s++;
    }
    return b;
}

int main()
{
    char s[MAXN];
    scanf("%s", s);
    if ( palindrome(s)==true )
        printf("true\n");
    else
        printf("false\n");
    
    return 0;
}