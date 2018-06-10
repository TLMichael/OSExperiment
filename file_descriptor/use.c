#include <unistd.h>

int main()
{
    char buf[80];
    int count;

    count = read(0, buf, sizeof(buf));
    buf[count] = 0;
    write(1, buf, count);
}
