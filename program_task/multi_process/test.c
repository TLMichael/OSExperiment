#include <stdio.h>
#include <unistd.h>
#include <errno.h>  
#include <sys/stat.h>
#include <fcntl.h>

int fd[2];
int flag;

void f1()
{
    int pid = fork();
    if (pid == 0) { 
        // child
        if(flag == 0)
        {
            dup2(fd[1], 1); 
            close(fd[0]);
            close(fd[1]);
            
            execlp("cat", "cat", "/etc/passwd", NULL);
            exit(0);
        }
        else if(flag == 1)
        {
            dup2(fd[0], 0); 
            close(fd[0]);
            close(fd[1]);
            
            execlp("wc", "wc", "-l", NULL);
            exit(0);
        }
    }
}


int pipe_sys(const char *cmdstring)
{
	pid_t pid;  
      
    pid = fork();
    if (pid == 0)  
    {  
		if(flag == 0)
		{
			dup2(fd[1], 1);
			close(fd[0]);
			close(fd[1]);
			execl("/bin/sh", "sh", "-c", cmdstring, (char *)0);  
        	exit(127); 
		}
		else if(flag == 1)
		{
			dup2(fd[0], 0);
			close(fd[0]);
			close(fd[1]);
			execl("/bin/sh", "sh", "-c", cmdstring, (char *)0);  
        	exit(127); 
		}
         
    }  
    return 0;  
}

int main()
{
    pipe(fd);

	flag = 0;
	pipe_sys("cat /etc/passwd");
	flag = 1;
	pipe_sys("wc -l");

    // flag = 0;
    // f1();
    // flag = 1;
    // f1();

    return 0;
}
