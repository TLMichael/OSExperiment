#include <stdio.h>
#include <unistd.h>
#include <errno.h>  
#include <sys/stat.h>
#include <fcntl.h>

int fd[2];
int fd_tmp[2];
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
            printf("[flag] %d\t[code] %s\n", flag, cmdstring);

			dup2(fd[1], 1);
			close(fd[0]);
			close(fd[1]);
			execl("/bin/sh", "sh", "-c", cmdstring, (char *)0);  
        	exit(127); 
		}
		else if(flag == 1)
		{
            printf("[flag] %d\t[code] %s\n", flag, cmdstring);

			dup2(fd[0], 0);
			close(fd[0]);
			close(fd[1]);
			execl("/bin/sh", "sh", "-c", cmdstring, (char *)0);  
        	exit(127); 
		}
        else if(flag == 2)
        {
            printf("[flag] %d\t[code] %s\n", flag, cmdstring);

            dup2(fd[0], 0);
            close(fd[0]);
            close(fd[1]);
            // 输出进入临时管道
            dup2(fd_tmp[1], 1);
            close(fd_tmp[0]);
            close(fd_tmp[1]);
            execl("/bin/sh", "sh", "-c", cmdstring, (char *)0);  
        	exit(127); 
        }
        wait(NULL);
    }  
    return 0;  
}

int main()
{
    pipe(fd);
    pipe(fd_tmp);

	flag = 0;
	pipe_sys("cat < input.txt");

	flag = 2;
	pipe_sys("sort");
    // 将临时管道变成正式的管道
    dup2(fd_tmp[0], fd[0]);
    dup2(fd_tmp[1], fd[1]);
    close(fd_tmp[0]);
    close(fd_tmp[1]);
    pipe(fd_tmp);
 
    flag = 2;
    pipe_sys("uniq");
    dup2(fd_tmp[0], fd[0]);
    dup2(fd_tmp[1], fd[1]);
    close(fd_tmp[0]);
    close(fd_tmp[1]);
    pipe(fd_tmp);

    flag = 1;
    pipe_sys("cat >output.txt");


    // flag = 0;
    // f1();
    // flag = 1;
    // f1();

    return 0;
}
