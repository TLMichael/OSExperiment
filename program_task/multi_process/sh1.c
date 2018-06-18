#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>  

#define MAX_BUFFLEN	1024
#define MAX_NUM 100

char *home;
char *dir;

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

int judge_buff(char *buff)
{
	if(buff[0] == '\0')
		return 0;
	char code[MAX_BUFFLEN];
	strcpy(code, buff);
	char *next = strchr(code, ' ');
	if(next != NULL)
		next[0] = '\0';
	//printf("[code] %s", code);
	if(strcmp(code, "cd") == 0)
		return 1;
	else if(strcmp(code, "exit") == 0)
		return 2;
	else 
		return 0;
}

int cd(char *buff)
{
	char code[MAX_BUFFLEN];
    char *argv[MAX_NUM];    // no more than 100 arguments
    int count = 0;      // N.O. of arguments
	char *next = NULL;
	char *rest = code;
	strcpy(code, buff);
	argv[count++] = code;
    while(next = strchr(rest, ' '))
    {
        next[0] = '\0';
        rest = next + 1;
        // printf("rest = \"%s\"\n", rest);
        
        if(rest[0] != '\0' && rest[0] != ' ')
            argv[count++] = rest;
        if(count + 2 > MAX_NUM)
            return 127;
    }
    argv[count++] = NULL;
	
	if(count == 2)
	{
		chdir(home);
		dir = getcwd(NULL, 0);
	}
	else
	{
		int res = chdir(argv[count - 2]);
		dir = getcwd(NULL, 0);
		if(res == -1)
		{
			printf("cd: No such path %s\n", argv[count - 2]);
			return -1;
		}
	}
	return 0;
}

int main()
{
	home = getenv("HOME");
	dir = getcwd(NULL, 0);

	char buff[MAX_BUFFLEN];
	printf("[%s]$ ", dir);
	while(gets(buff))
	{
		int res = judge_buff(buff);
		if(res == 0)
			mysys(buff);
		else if(res == 1)
			cd(buff);
		else if(res == 2)
			return 0;
		printf("[%s]$ ", dir);
	}



	mysys("pwd");
    mysys("echo ,HELLO  WORLD ,  sdfa sdfadf        ss   ");
    mysys("echo /G");
    mysys("echo ,,");
    mysys("echo");



    return 0;
}
