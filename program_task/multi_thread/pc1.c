#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

#define CAPACITY 4
char buffer1[CAPACITY];
char buffer2[CAPACITY];
int in1, in2;
int out1, out2;

int buffer_is_empty(int n)
{
    if(n == 1)
        return in1 == out1;
    else if(n == 2)
        return in2 == out2;
    else
        exit(-1);
}

int buffer_is_full(int n)
{
    if( n == 1)
        return (in1 + 1) % CAPACITY == out1;
    else if(n == 2)
        return (in2 + 1) % CAPACITY == out2;
}

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

#define ITEM_COUNT (CAPACITY * 2)
pthread_mutex_t mutex1, mutex2;
pthread_cond_t wait_empty_buffer1, wait_empty_buffer2;
pthread_cond_t wait_full_buffer1, wait_full_buffer2;

void *consume(void *arg)
{
    int item;
    for(int i = 0; i < ITEM_COUNT; i++)
    {
        pthread_mutex_lock(&mutex2);
        while(buffer_is_empty(2))
            pthread_cond_wait(&wait_full_buffer2, &mutex2);
        
        item = get_item(2);
        printf("\033[34m consume item: %c\n\033[0m", item);     //蓝色为消费者

        pthread_cond_signal(&wait_empty_buffer2);
        pthread_mutex_unlock(&mutex2);
    }
    return NULL;
}

void *compute(void *arg)
{
    char item;
    for(int i = 0; i < ITEM_COUNT; i++)
    {
        pthread_mutex_lock(&mutex1);
        while(buffer_is_empty(1))
            pthread_cond_wait(&wait_full_buffer1, &mutex1);
        item = get_item(1);
        pthread_cond_signal(&wait_empty_buffer1);
        pthread_mutex_unlock(&mutex1);

        item += 'A' - 'a';

        pthread_mutex_lock(&mutex2);
        while(buffer_is_full(2))
            pthread_cond_wait(&wait_empty_buffer2, &mutex2);
        put_item(item, 2);
        printf("\033[33m compute item: %c\n\033[0m", item);     //黄色为计算者

        pthread_cond_signal(&wait_full_buffer2);
        pthread_mutex_unlock(&mutex2);

    }
    return NULL;
}

void *produce(void *arg)
{
    char item;
    for(int i = 0; i < ITEM_COUNT; i++)
    {
        pthread_mutex_lock(&mutex1);
        while(buffer_is_full(1))
            pthread_cond_wait(&wait_empty_buffer1, &mutex1);
        item = 'a' + i;
        put_item(item, 1);
        printf("\033[31m produce item: %c\n\033[0m", item);     //红色为生产者

        pthread_cond_signal(&wait_full_buffer1);
        pthread_mutex_unlock(&mutex1);
    }
    return NULL;
}

int main()
{
    pthread_t producer_tid, computer_tid, consumer_tid;

    pthread_mutex_init(&mutex1, NULL);
    pthread_mutex_init(&mutex2, NULL);
    pthread_cond_init(&wait_empty_buffer1, NULL);
    pthread_cond_init(&wait_empty_buffer2, NULL);
    pthread_cond_init(&wait_full_buffer1, NULL);
    pthread_cond_init(&wait_full_buffer2, NULL);

    pthread_create(&producer_tid, NULL, produce, NULL);
    pthread_create(&computer_tid, NULL, compute, NULL);
    pthread_create(&consumer_tid, NULL, consume, NULL);

    pthread_join(producer_tid, NULL);
    pthread_join(computer_tid, NULL);
    pthread_join(consumer_tid, NULL);

    return 0;
}