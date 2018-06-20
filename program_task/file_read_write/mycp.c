#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<fcntl.h>
#include<unistd.h>

int main(int argc, char** argv)
{
	int infile, outfile;
	char buf[1024];
	int num;
	if(argc != 3)
	{
		printf("The format must be:cp file_src file_des");
		exit(0);
	}

	if((infile = open(argv[1], O_RDONLY)) == -1)
	{
		perror("open1");
		exit(0);
	}

	if((outfile = open(argv[2], O_CREAT | O_EXCL | O_WRONLY, 0644)) == -1)
	{
		perror("open2");
		exit(0);
	}

	do
	{
		num = read(infile, buf, 1024);
		write(outfile, buf, num);
	}while(num == 1024);

	close(infile);
	close(outfile);
	return 0;
}
