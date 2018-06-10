#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>

int main()
{
    printf("pid = %x, ppid = %x\n", getpid(), getppid());
    return 0;
}
