// 题目3
// 1.主线程创建10个子线程 
//     - 第0个子线程计算从01加到10的和 
//     - 第1个子线程计算从11加到20的和 
//     - 第2个子线程计算从21加到30的和 
//     - ... 
//     - 第9个子线程计算从91加到100的和 
// 2. 主线程归并10个子线程的计算结果，最终结果为5050 
// 3. 本题必须使用线程参数来完成

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define N 10
#define NR_TOTAL 100
#define NR_CPU N
#define NR_CHILD (NR_TOTAL / NR_CPU)

typedef struct param {
	int start;
	int end;
}Param;

typedef struct result {
	float sum;
}Result;

void *compute(void *arg)
{
    Param *param = (Param *)arg;
    Result *result;
    int sum = 0;
    for(int i = param->start + 1; i < param->end + 1; i++)
        sum+= i;
    
    result = malloc(sizeof(Result));
    result->sum = sum;
    return result;
}

int main()
{
    pthread_t workers[NR_CPU];
    Param params[NR_CPU];
    int total = 0;

    for(int i = 0; i < NR_CPU; i++)
    {
        Param *param;
        param = &params[i];
        param->start = i * NR_CHILD;
        param->end = (i+1) * NR_CHILD;
        pthread_create(&workers[i], NULL, compute, param);
    }

    for(int i = 0; i < NR_CPU; i++)
    {
        Result *result;
        pthread_join(workers[i], (void**)&result);
        total += result->sum;
        free(result);
    }

    printf("Total = %d\n", total);
    return 0;
}