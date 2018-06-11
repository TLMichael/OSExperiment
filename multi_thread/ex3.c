#include <stdio.h>
#include <pthread.h>

int array[] = {1, 1, 1, 2, 2, 2};
#define NUMBER 6

int worker_output;

void *worker(void *arg)
{
	int i;
	for(i = 0; i < NUMBER / 2; i++)
		worker_output += array[i];
	return NULL;
}

int master_output;

void master()
{
	int i;

	for (i = NUMBER / 2; i < NUMBER; i++)
		master_output += array[i];
}

int main()
{
	pthread_t worker_tid;
	int total;

	pthread_create(&worker_tid, NULL, worker, NULL);
	master();
	pthread_join(worker_tid, NULL);
	total = master_output + worker_output;
	printf("master_output = %d, worker_output = %d, total = %d\n", master_output, worker_output, total);
	return 0;
}
