#include <stdio.h>
#include <unistd.h>
#include <string.h>

int mysys(char *arg)
{
    char code[1024];
    strcpy(code, arg);
    //printf("code = %s\n", code);
    char *next = strchr(code, ' ');
    char *rest = next + 1;
    next[0] = '\0';

    printf("code = %s\n", code);
    printf("rest = %s\n", rest);
    
    

    return 0;
}

int main()
{
    mysys("echo HELLO WORLD");

    printf("----------------------------------------------------------\n");
    system("echo HELLO WORLD");
    printf("----------------------------------------------------------\n");
    system("ls /");
    printf("----------------------------------------------------------\n");

    return 0;
}
