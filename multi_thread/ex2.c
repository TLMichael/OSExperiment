#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

void *compute(void *arg)
{
	char *string = arg;
	int i;

	for(i = 0; i < 3; i++)
	{
		puts(string);
		sleep(1);
	}
	return NULL;
}

int main()
{
	pthread_t worker_tid;
	pthread_create(&worker_tid, NULL, &compute, "worker");
	compute("master");
	return 0;
}
