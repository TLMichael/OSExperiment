#include <stdio.h>
#include <unistd.h>
#include <string.h>

#define MAX_BUFFLEN	1024
#define MAX_NUM 100

int mysys(char *arg)
{
	if(arg[0] == '\0')
		return 127;

    char code[MAX_BUFFLEN];
    char *argv[MAX_NUM];    // no more than 100 arguments
    int count = 0;      // N.O. of arguments
	char *next = NULL;
	char *rest = code;

	strcpy(code, arg);

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

    // printf("[argv]\n");
    // for(size_t i = 0; i < count; i++)
    //     printf("\t[%d] %s\n", i, argv[i]);

	int pid;
	pid = fork();
	if(pid == 0)
	{
		int error = execvp(code, argv);
		if(error < 0)
		{
			perror("execvp");
			return 127;
		}
		else
			return 0;
	}

	int status;
	wait(&status);
	return status;
}

int main()
{
	//char *argv[] = {"ls", "/", NULL};
	//execvp("ls", argv);

    mysys("echo ,HELLO  WORLD ,  sdfa sdfadf        ss   ");
    mysys("echo /G");
    mysys("echo ,,");
    mysys("echo");

    mysys("asdfasdf");


    printf("----------------------------------------------------------\n");
    mysys("echo HELLO WORLD");
    printf("----------------------------------------------------------\n");
    mysys("ls /");
    printf("----------------------------------------------------------\n");

    return 0;
}
