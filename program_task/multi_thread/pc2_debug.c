#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

#define CAPACITY 4
#define ITEM_COUNT (CAPACITY * 2)
char buffer1[CAPACITY];
char buffer2[CAPACITY];
int in1, in2;
int out1, out2;

char get_item(int n)
{
    char item;
    if(n == 1)
    {
        item = buffer1[out1];
        out1 = (out1 + 1) % CAPACITY;
    }
    else if(n == 2)
    {
        item = buffer2[out2];
        out2 = (out2 + 1) % CAPACITY;
    }
    else
        exit(-1);
    return item;
}

void put_item(char item, int n)
{
    if(n == 1)
    {
        buffer1[in1] = item;
        in1 = (in1 + 1) % CAPACITY;
    }
    else if(n == 2)
    {
        buffer2[in2] = item;
        in2 = (in2 + 1) % CAPACITY;
    }
    else 
        exit(-1);
}

typedef struct {
    int value;
    pthread_mutex_t mutex;
    pthread_cond_t cond;
}sema_t;

void sema_init(sema_t *sema, int value)
{  
    sema->value = value;
    pthread_mutex_init(&sema->mutex, NULL);
    pthread_cond_init(&sema->cond, NULL);
}

void sema_wait(sema_t *sema)
{
    //printf("[debug] start = %d\n", sema->value);
    pthread_mutex_lock(&sema->mutex);
    int i = 1;
    while(sema->value <= 0)
    {
        printf("waiting for sema %d\n", i++);
        pthread_cond_wait(&sema->cond, &sema->mutex);
    }
    sema->value--;
    pthread_mutex_unlock(&sema->mutex);
    //printf("[debug] end = %d\n", sema->value);
}

void sema_signal(sema_t *sema)
{
    pthread_mutex_lock(&sema->mutex);
    sema->value += 1;
    pthread_cond_signal(&sema->cond);
    pthread_mutex_unlock(&sema->mutex);
}

sema_t mutex_sema1, mutex_sema2;
sema_t empty_buffer_sema1, empty_buffer_sema2;
sema_t full_buffer_sema1, full_buffer_sema2;

void *consume(void *arg)
{
    int item;
    for(int i = 0; i < ITEM_COUNT; i++)
    {
        //printf("[debug] In consume\n");
        sema_wait(&full_buffer_sema2);
        printf("consume get full_buffer_sema2\n");
        sema_wait(&mutex_sema2);
        printf("consume get mutex_sema2\n");
        
        item = get_item(2);
        printf("\033[34m consume item: %c\n\033[0m", item);     //蓝色为消费者

        sema_signal(&mutex_sema2);
        printf("consume release mutex_sema2\n");
        sema_signal(&empty_buffer_sema2);
        printf("consume release empty_buffer_sema2\n");
    }
    return NULL;
}

void *compute(void *arg)
{
    char item;
    for(int i = 0; i < ITEM_COUNT; i++)
    {
        //printf("[debug] In compute\n");
        sema_wait(&full_buffer_sema1);
        printf("compute get full_buffer_sema1\n");
        sema_wait(&mutex_sema1);
        printf("compute get mutex_sema1\n");
        item = get_item(1);
        sema_signal(&mutex_sema1);
        printf("compute release mutex_sema1\n");
        sema_signal(&empty_buffer_sema1);
        printf("compute release empty_buffer_sema1\n");

        item += 'A' - 'a';

        sema_wait(&empty_buffer_sema2);
        printf("compute get empty_buffer_sema2\n");
        sema_wait(&mutex_sema2);
        printf("compute get mutex_sema2\n");
        put_item(item, 2);
        printf("\033[33m compute item: %c\n\033[0m", item);     //黄色为计算者
        sema_signal(&mutex_sema2);
        printf("compute release mutex_sema2\n");
        sema_signal(&full_buffer_sema2);
        printf("compute release full_buffer_sema2\n");

    }
    return NULL;
}

void *produce(void *arg)
{
    char item;
    for(int i = 0; i < ITEM_COUNT; i++)
    {
        //printf("[debug] In produce\n");
        sema_wait(&empty_buffer_sema1);
        printf("produce get empty_buffer_sema1\n");
        sema_wait(&mutex_sema1);
        printf("produce get mutex_sema1\n");
        item = 'a' + i;
        put_item(item, 1);
        printf("\033[31m produce item: %c\n\033[0m", item);     //红色为生产者
        sema_signal(&mutex_sema1);
        printf("produce release mutex_sema1\n");
        sema_signal(&full_buffer_sema1);
        printf("produce release full_buffer_sema1\n");
    }
    return NULL;
}

int main()
{
    pthread_t producer_tid, computer_tid, consumer_tid;

    sema_init(&mutex_sema1, 1);
    sema_init(&mutex_sema2, 1);
    sema_init(&empty_buffer_sema1, CAPACITY - 1);
    sema_init(&empty_buffer_sema2, CAPACITY - 1);
    sema_init(&full_buffer_sema1, 0);
    sema_init(&full_buffer_sema2, 0);

    pthread_create(&producer_tid, NULL, produce, NULL);
    pthread_create(&computer_tid, NULL, compute, NULL);
    pthread_create(&consumer_tid, NULL, consume, NULL);

    pthread_join(producer_tid, NULL);
    pthread_join(computer_tid, NULL);
    pthread_join(consumer_tid, NULL);

    return 0;
}