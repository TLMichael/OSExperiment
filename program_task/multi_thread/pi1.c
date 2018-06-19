#include <stdio.h>
#include <pthread.h>

int N = 1000000;

float worker_output;
float master_output;

int sign(int n)
{
	if(n % 2 == 0)
		return 1;
	else
		return -1;
}

void *worker(void *arg)
{
	int i;
	for(i = N / 2; i < N; i++)
		worker_output += (float)sign(i) / (2*i + 1);
	
	printf("worker_output = %.10f\n", worker_output);
	return NULL;
}

void master()
{
	for(int i = 0; i < N / 2; i++)
		master_output += (float)sign(i) / (2*i + 1);
	
	printf("master_output = %.10f\n", master_output);
	return;
}

int main()
{
	pthread_t worker_tid;
	float total;

	pthread_create(&worker_tid, NULL, worker, NULL);
	master();
	pthread_join(worker_tid, NULL);
	total = worker_output + master_output;
	printf("PI = %.10f\n", total * 4);
	return 0;
}
