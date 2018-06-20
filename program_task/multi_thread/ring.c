#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

#define N 100
int buff[N];

typedef struct {
    int value;
    pthread_mutex_t mutex;
    pthread_cond_t cond;
} sema_t;

typedef struct {
    int order;
} Param;

void sema_init(sema_t *sema, int value)
{
    sema->value = value;
    pthread_mutex_init(&sema->mutex, NULL);
    pthread_cond_init(&sema->cond, NULL);
}

void sema_wait(sema_t *sema)
{
    pthread_mutex_lock(&sema->mutex);
    while(sema->value <= 0)
        pthread_cond_wait(&sema->cond, &sema->mutex);
    sema->value--;
    pthread_mutex_unlock(&sema->mutex);
}

void sema_signal(sema_t *sema)
{
    pthread_mutex_lock(&sema->mutex);
    ++sema->value;
    pthread_cond_signal(&sema->cond);
    pthread_mutex_unlock(&sema->mutex);
}

sema_t mutex_sema[N];
sema_t full_buffer_sema[N];

void *add(void *arg)
{
    int receive;
    Param *param = (Param *)arg;
    int order = param->order;
    if(order == 0)
    {
        sema_wait(&mutex_sema[order + 1]);
        buff[order + 1] = 1;
        sema_signal(&mutex_sema[order + 1]);
        sema_signal(&full_buffer_sema[order + 1]);

        sema_wait(&full_buffer_sema[order]);
        sema_wait(&mutex_sema[order]);
        receive = buff[order];
        printf("Thread %d received: %d\n", order + 1, receive);
        sema_signal(&mutex_sema[order]);
    }
    else if(order == N - 1)
    {
        sema_wait(&full_buffer_sema[order]);
        sema_wait(&mutex_sema[order]);
        receive = buff[order];
        printf("Thread %d received: %d\n", order + 1, receive);
        sema_signal(&mutex_sema[order]);
        
        sema_wait(&mutex_sema[0]);
        buff[0] = receive + 1;
        sema_signal(&mutex_sema[0]);
        sema_signal(&full_buffer_sema[0]);
    }
    else
    {
        sema_wait(&full_buffer_sema[order]);
        sema_wait(&mutex_sema[order]);
        receive = buff[order];
        printf("Thread %d received: %d\n", order + 1, receive);
        sema_signal(&mutex_sema[order]);

        sema_wait(&mutex_sema[order + 1]);
        buff[order + 1] = receive + 1;
        sema_signal(&mutex_sema[order + 1]);
        sema_signal(&full_buffer_sema[order + 1]);
    }
}

int main()
{
    pthread_t ring_tid[N];
    Param params[N];
    for(int i = 0; i < N; i++)
    {
        sema_init(&mutex_sema[i], 1);
        sema_init(&full_buffer_sema[i], 0);
    }

    for(int i = 0; i < N; i++)
    {
        params[i].order = i;
        pthread_create(&ring_tid[i], NULL, add, &params[i]);
    }

    for(int i = 0; i < N; i++)
        pthread_join(ring_tid[i], NULL);
    
    return 0;
}