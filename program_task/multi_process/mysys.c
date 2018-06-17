#include <stdio.h>
#include <unistd.h>
#include <string.h>

int mysys(char *arg)
{
    char code[1024];
    char *argv[100];    //no more than 100 arguments
    int count = 0;      //n.o. of arguments
    strcpy(code, arg);
    //printf("code = %s\n", code);
    char *next = strchr(code, ' ');
    char *rest = next + 1;
    next[0] = '\0';

    printf("code = \"%s\"\n", code);
    printf("rest = \"%s\"\n", rest);
    
    while(next = strchr(rest, ' '))
    {
        next[0] = '\0';
        rest = next + 1;
        printf("rest = \"%s\"\n", rest);
        
        if(rest[0] != '\0' && rest[0] != ' ')
            argv[count++] = rest;
    }
    
    printf("[argv]\n");
    for(int i = 0; i < count; i++)
        printf("[%d] %s\n", i, argv[i]);

    return 0;
}

int main()
{
    mysys("echo  ,HELLO  WORLD ,  sdfa sdfadf        ss   ");
    mysys("echo  ");
    mysys("echo ");
    mysys("echo");


    printf("----------------------------------------------------------\n");
    system("echo HELLO WORLD");
    printf("----------------------------------------------------------\n");
    system("ls /");
    printf("----------------------------------------------------------\n");

    return 0;
}
