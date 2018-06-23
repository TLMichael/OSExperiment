// 题目2
// 主进程创建2个子进程，主进程通过两个管道分别与两个子进程连接
// 第一个子进程计算从1加到50的和，并将结果通过管道送给父进程
// 第一个子进程计算从50加到100的和，并将结果通过管道送给父进程
// 父进程读取两个子进程的结果，将他们相加，打印出来，结果为5050

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
    int fd1[2];
    int fd2[2];
    pipe(fd1);
    pipe(fd2);

    pid_t pid1;
    pid1 = fork();
    if(pid1 == 0)
    {
        close(fd1[0]);
        int sum = 0;
        for(int i = 1; i <= 50; i++)
            sum += i;
        write(fd1[1], &sum, sizeof(int));
        exit(-1);
    }
    pid_t pid2;
    pid2 = fork();
    if(pid2 == 0)
    {
        close(fd2[0]);
        int sum = 0;
        for(int i = 51; i <= 100; i++)
            sum += i;
        write(fd2[1], &sum, sizeof(int));
        exit(-1);
    }

    int p1, p2;
    close(fd1[1]);
    close(fd2[1]);
    read(fd1[0], &p1, sizeof(int));
    read(fd2[0], &p2, sizeof(int));

    printf("%d\n", p1 + p2);

    return 0;
}