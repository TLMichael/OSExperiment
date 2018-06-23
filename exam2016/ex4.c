// 题目4
// 主线程创建4个子线程T1、T2、T3、T4，主线程在4个子线程退出后，才退出
// 线程T1、T2、T3、T4的运行时代码如下：
// #include <unistd.h> // sleep函数声明在该头文件中

// void *T1_entry(void *arg)
// {
//     sleep(2);  // 睡眠2秒，不准删除此条语句，否则答题无效
//     puts(“T1”);
// }

// void *T2_entry(void *arg)
// {
//     sleep(1);  // 睡眠1秒，不准删除此条语句，否则答题无效
//     puts(“T2”);
// }

// void *T3_entry(void *arg)
// {
//     sleep(1);  // 睡眠1秒，不准删除此条语句，否则答题无效
//     puts(“T3”);
// }

// void *T4_entry(void *arg)
// {
//     puts(“T4”);
// }
// 使用信号量或者条件变量机制(而不是使用sleep函数)，使得这四个线程满足如下制约关系：
// T1的print语句执行后，T2和T3才可以执行print语句
// T2和T3的print语句执行后，T4才可以执行print语句
// 程序输出结果为
// T1
// T2
// T3
// T4
// 或者

// T1
// T3
// T2
// T4

#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

#define N 4
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

sema_t full_buffer_sema[N];

void *T1_entry(void *arg)
{
    sleep(2);  // 睡眠2秒，不准删除此条语句，否则答题无效

    puts("T1");
    sema_signal(&full_buffer_sema[0]);
    sema_signal(&full_buffer_sema[0]);

    return NULL;
}

void *T2_entry(void *arg)
{
    sleep(1);  // 睡眠1秒，不准删除此条语句，否则答题无效

    sema_wait(&full_buffer_sema[0]);
    puts("T2");
    sema_signal(&full_buffer_sema[1]);

    return NULL;
}

void *T3_entry(void *arg)
{
    sleep(1);  // 睡眠1秒，不准删除此条语句，否则答题无效

    sema_wait(&full_buffer_sema[0]);
    puts("T3");
    sema_signal(&full_buffer_sema[2]);
    
    return NULL;
}

void *T4_entry(void *arg)
{
    sema_wait(&full_buffer_sema[1]);
    sema_wait(&full_buffer_sema[2]);
    puts("T4");

    return NULL;
}

int main()
{
    pthread_t tid[4];

    for(int i = 0; i < N; i++)
        sema_init(&full_buffer_sema[i], 0);
    
    pthread_create(&tid[0], NULL, T1_entry, NULL);
    pthread_create(&tid[1], NULL, T2_entry, NULL);
    pthread_create(&tid[2], NULL, T3_entry, NULL);
    pthread_create(&tid[3], NULL, T4_entry, NULL);

    for(int i = 0; i < N; i++)
        pthread_join(tid[i], NULL);

    return 0;
}