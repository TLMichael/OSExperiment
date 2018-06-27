// main.c
#include <stdio.h>

int add(int x, int y);

int main()
{
    int a = 89;
    int b = 11;
    int res = add(a, b);
    printf("%d + %d = %d\n", a, b, res);
    return 0;
}