// 题目1
// 主进程创建1个子进程
// 主进程通过管道与子进程连接
// 子进程的标准输出连接到管道的写端
// 主进程的标准输入连接到管道的读端
// 在子进程中调用exec(“echo”, “echo”, “hello world”, NULL)
// 在父进程中调用read(0, buf, sizeof(buf))，从标准输入中获取子进程发送的字符串，并打印出来



#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>  
#include <sys/stat.h>
#include <fcntl.h>

int main()
{
    int fd[2];
    pipe(fd);

    pid_t pid;
    pid = fork();
    if(pid == 0)
    {
        dup2(fd[1], 1);
        close(fd[0]);
        close(fd[1]);
        execlp("echo", "echo", "hello world", NULL);
        printf("child process exec failed.\n");
    }
    else
    {
        dup2(fd[0], 0);
        close(fd[0]);
        close(fd[1]);
        char buf[1024];
        int readsize = read(0, buf, sizeof(buf));
        write(1, buf, readsize);
    }

    wait(NULL);
    return 0;
}