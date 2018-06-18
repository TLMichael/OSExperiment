#include <stdio.h>
#include <stdlib.h> 
#include <unistd.h>
#include <string.h>
#include <errno.h>  
#include <sys/types.h>

#define MAX_BUFFLEN	1024
#define MAX_NUM 100

int mysys(const char *cmdstring)
{
	pid_t pid;  
    int status = -1;  
  
    if (cmdstring == NULL)  
        return 1;  
      
    if ((pid = fork()) < 0)  
        status = -1;  
    else if (pid == 0)  
    {  
        execl("/bin/sh", "sh", "-c", cmdstring, (char *)0);  
        exit(127);  
    }  
    else  
    {  
        while (waitpid(pid, &status, 0) < 0)  
        {  
            if (errno != EINTR)  
            {  
               status = -1;  
               break;  
            }  
        }  
    }  
  
    return status;  
}

int main()
{
	//char *argv[] = {"ls", "/", NULL};
	//execvp("ls", argv);
    int res;
    res = mysys("");
    printf("[Status] %d\n", res);
	res = mysys("pwd");
    printf("[Status] %d\n", res);
    res = mysys("echo ,HELLO  WORLD ,  sdfa sdfadf        ss   ");
    printf("[Status] %d\n", res);
    res = mysys("echo /G");
    printf("[Status] %d\n", res);
    res = mysys("echo ,,");
    printf("[Status] %d\n", res);
    res = mysys("echo");
    printf("[Status] %d\n", res);

    res = mysys("asdfasdf");
    printf("[Status] %d\n", res);


    printf("----------------------------------------------------------\n");
    res = mysys("echo HELLO WORLD");
    printf("[Status] %d\n", res);
    printf("----------------------------------------------------------\n");
    res = mysys("ls /");
    printf("[Status] %d\n", res);
    printf("----------------------------------------------------------\n");

    return 0;
}
