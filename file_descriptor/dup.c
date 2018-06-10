#include <stdio.h>
#include <unistd.h> 
#include <sys/stat.h> 
#include <fcntl.h>  
// void dup2(oldfd, newfd); 
// fd_table[newfd] = fd_table[oldfd]; 
int main() 
{     
	int fd;     
	fd = open("log.txt", O_CREAT|O_RDWR, 0666);     
	dup2(fd, 1);     
	close(fd);     
	write(1, "hello\n", 6);     
	puts("world");     
	return 0; 
}
