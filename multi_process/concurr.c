#include <stdio.h>
#include <unistd.h>

void child()
{
    int i;
    for(i = 0; i < 3; i++)
    {
	puts("child");
	sleep(1);
    }
}

void parent()
{
    int i;
    for(i = 0; i < 3; i++)
    {
	puts("parent");
	sleep(1);
    }
}

int main()
{
    pid_t pid;

    pid = fork();
    if(pid == 0)
	child();
    else
	parent();
    return 0;
}
