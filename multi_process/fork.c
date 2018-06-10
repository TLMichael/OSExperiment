#include <stdio.h>
#include <unistd.h>

int main()
{
    printf("[debug] my pid: %d\n", getpid());
    pid_t pid;
    
    pid = fork();
    if(pid == 0)
	printf("In child:  child PID = %d, parent PID = %d\n", getpid(), getppid());
    else
	printf("In parent: child PID = %d, parent PID = %d\n", pid, getpid());
    return 0;
}
