#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

void *compute(void *arg)
{
	char i;
	for(i = 'a'; i < 'd'; i++)
	{
		printf("worker: %c\n", i);
		sleep(1);
	}
	return NULL;
}

int main()
{
	pthread_t worker_tid;
	pthread_create(&worker_tid, NULL, &compute, NULL);

	char i;
	for(i = 'A'; i < 'D'; i++)
	{
		printf("master: %c\n", i);
		sleep(1);
	}
	return 0;
}
