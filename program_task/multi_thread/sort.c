#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <string.h>

#define NUMMAX 100
int nums[NUMMAX];

typedef struct param {
    int start;
    int end;
}Param;

void show_nums(int *arr, const char *str)
{   
    printf("[%s]\n", str);
    for(int i = 0; i < NUMMAX; i++)
    {
        if(i == 0)
            printf("\t");
        else if(i % 10 == 0)
            printf("\n\t");
        printf("%6d", arr[i]);
    }
    printf("\n");
}

void generate_nums()
{
    srandom(time(NULL));
    for(int i = 0; i < NUMMAX; i++)
        nums[i] = rand() % 10000;
}

//快速排序
int findPos(int data[], int low, int high) {
    //将大于t的元素赶到t的左边，大于t的元素赶到t的右边
    int t = data[low];
    while(low < high) {
        while(low < high && data[high] >= t) {
            high--;
        }
        data[low] = data[high];
        while(low < high && data[low] <=t) {
            low++;
        }
        data[high] = data[low];
    }
    data[low] = t;
    //返回此时t在数组中的位置
    return low;
}

void quickSort(int data[], int low, int high) {
    if(low > high) {
        return;
    }
    int pos = findPos(data, low, high);
    quickSort(data, low, pos-1);
    quickSort(data, pos+1, high); 
}

//冒泡排序
void bubleSort(int data[], int n) {
    int i,j,temp;
    for(j=0;j<n-1;j++) {
        for(i=0;i<n-j-1;i++) {
            if(data[i]>data[i+1]) {
                temp = data[i];
                data[i] = data[i+1];
                data[i+1] = temp;
            }
        }
    }  
}

int compare(const void *a, const void *b)
{
    return (*(int*)a - *(int*)b);
}
//使用stdlib.h里面的qsort()
void *sort(void *arg)
{
    Param *param = (Param *)arg;
    int left = param->start;
    int right = param->end;
    if(left >= right)
        return NULL;
    qsort(nums + left, right - left, sizeof(int), compare);
    return NULL;
}

void merge(const int left, const int mid, const int right)
{
    int temp[NUMMAX];
    memcpy(temp, nums, NUMMAX * sizeof(int));
    //show_nums(temp, "temp");
    int s1 = left;
    int s2 = mid + 1;
    int t = left;
    while(s1 <= mid && s2 <= right)
    {
        if(temp[s1] < temp[s2])
            nums[t++] = temp[s1++];
        else
            nums[t++] = temp[s2++];
    }
    while(s1 <= mid)
        nums[t++] = temp[s1++];
    while(s2 <= right)
        nums[t++] = temp[s2++];
}

int main()
{
    generate_nums();
    show_nums(nums, "unsort");

    pthread_t worker_tid;
    Param params[2];
    params[0].start = 0;
    params[0].end = NUMMAX / 2;
    params[1].start = NUMMAX / 2;
    params[1].end = NUMMAX;

    pthread_create(&worker_tid, NULL, sort, &params[1]);
    //sort(&params[1]);
    sort(&params[0]);

    pthread_join(worker_tid, NULL);
    merge(0, NUMMAX / 2 - 1, NUMMAX - 1);

    show_nums(nums, "sorted");
    return 0;
}