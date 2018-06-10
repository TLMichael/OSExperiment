#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

void child()
{
	exit(123);
}

int main()
{
	int pid;
	pid = fork();
	if(pid == 0)
		child();

	int status;
	wait(&status);
	if(WIFEXITED(status))
	{
		printf("WIFEXITED = true\n");
		printf("WEXITSTATUS = %d\n", WEXITSTATUS(status));
	}
	return 0;
}
