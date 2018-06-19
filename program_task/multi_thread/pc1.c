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
    return NULL;
}

void *compute(void *arg)
{
    return NULL;
}

void *produce(void *arg)
{
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