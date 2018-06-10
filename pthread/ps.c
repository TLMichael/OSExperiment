#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

void *myThread1(void)
{
    int i;
    for (i=0; i<100; i++)
    {
        printf("This is the 1st pthread,created by zieckey.");
        sleep(1);//Let this thread to sleep 1 second,and then continue to run
    }
}

void *myThread2(void)
{
    int i;
    for (i=0; i<100; i++)
    {
        printf("This is the 2st pthread,created by zieckey.");
        sleep(1);
    }
}

int main()
{
    int i=0, ret=0;
    pthread_t id1,id2;
 
    ret = pthread_create(&id2, NULL, (void*)myThread1, NULL);
    if (ret)
    {
        printf("Create pthread error!/n");
        return 1;
    }
  
    ret = pthread_create(&id2, NULL, (void*)myThread2, NULL);
    if (ret)
    {
        printf("Create pthread error!/n");
        return 1;
    }
  
    pthread_join(id1, NULL);
    pthread_join(id2, NULL);
					   
    return 0;
}
