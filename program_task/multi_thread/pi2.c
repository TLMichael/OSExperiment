#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define N 8

#define NR_TOTAL 1000000
#define NR_CPU	N
#define NR_CHILD (NR_TOTAL/NR_CPU)

typedef struct param {
	int start;
	int end;
}Param;

typedef struct result {
	float sum;
}Result;

int sign(int n)
{
	if(n % 2 == 0)
		return 1;
	else
		return -1;
}

void *compute(void *arg)
{	
	Param *param = (Param *)arg;
	Result *result;
	float sum = 0;
	for(int i = param->start; i < param->end; i++)
		sum += (float)sign(i) / (2 * i + 1);
	
	printf("worker %d = %.10f\n", param->start / NR_CHILD, sum);
	result = malloc(sizeof(Result));
	result->sum = sum;
	return result;
}

int main()
{
	pthread_t workers[NR_CPU];
	Param params[NR_CPU];
	float total = 0;

	for(int i = 0; i < NR_CPU; i++)
	{
		Param *param;
		param = &params[i];
		param->start = i * NR_CHILD;
		param->end = (i + 1) * NR_CHILD;
		pthread_create(&workers[i], NULL, compute, param);
	}

	for(int i = 0; i < NR_CPU; i++)
	{
		Result *result;
		pthread_join(workers[i], (void **)&result);
		total += result->sum;
		free(result);
	}

	printf("PI = %.10f\n", total * 4);
	return 0;
}
