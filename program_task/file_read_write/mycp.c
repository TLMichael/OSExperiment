// #include<stdio.h>
// #include<string.h>
// #include<stdlib.h>
// #include<fcntl.h>

// int main(int argc, char** argv)
// {
// 	int infile, outfile;
// 	char buf[1024];
// 	int num;
// 	if(argc != 3)
// 	{
// 		printf("The format must be:cp file_src file_des");
// 		exit(0);
// 	}

// 	if((infile = open(argv[1], O_RDONLY)) == -1)
// 	{
// 		perror("open1");
// 		exit(0);
// 	}

// 	if((outfile = open(argv[2], O_CREAT | O_EXCL | O_WRONLY, 0644)) == -1)
// 	{
// 		perror("open2");
// 		exit(0);
// 	}

// 	do
// 	{
// 		num = read(infile, buf, 1024);
// 		write(outfile, buf, num);
// 	}while(num == 1024);

// 	close(infile);
// 	close(outfile);
// 	return 0;
// }

#include<stdio.h>

int copy_file(FILE *src, FILE *dest)
{
	int c;
	while((c = getc(src)) != EOF)
		putc(c, dest);
	return c;
}

int main(int argc, char** argv)
{
	if(argc != 3)
	{
		printf("mycp: missing file operand\n");
		return -1;
	}

	FILE *infile, *outfile;
	if((infile = fopen(argv[1], "r")) == NULL)
	{
		printf("mycp: %s: No such file or directory\n", argv[1]);
		return -1;
	}
	if((outfile = fopen(argv[2], "a")) == NULL)
	{
		printf("mycp: %s: Can't create file\n", argv[2]);
		return -1;
	}
	copy_file(infile, outfile);
	fclose(infile);
	fclose(outfile);

	return 0;
}
