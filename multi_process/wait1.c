#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

void child()
{
	puts("Child process");
	exit(123);
}

int main()
{
	int pid;
	pid = fork();
	if(pid == 0)
		child();
	wait(NULL);
	puts("Parent process");
	return 0;
}
