#include <stdio.h>
#include <pthread.h>

volatile int global = 0;

void *compute(void *arg)
{
	int i;
	for(i = 0; i < 100 * 100 * 100; i++)
	{
		global++;
	}
	return NULL;
}

int main()
{
	int i;
	pthread_t tids[3];

	global = 0;
	for(i = 0; i < 3; i++)
		pthread_create(&tids[i], NULL, compute, NULL);

	for(i = 0; i < 3; i++)
		pthread_join(tids[i], NULL);
	printf("global = %d\n", global);
	return 0;
}

