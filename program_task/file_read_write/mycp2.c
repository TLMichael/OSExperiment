#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<fcntl.h>
#include<unistd.h>

int copy_file(int infile, int outfile)
{
    int num;
    char buf[1];
    do{
        num = read(infile, buf, 1);
        write(outfile, buf, num);
    }while(num == 1);
}

int main(int argc, char** argv)
{
    int infile, outfile;

    if(argc != 3)
    {
        printf("The format must be:cp file_src file_des");
		exit(0);
    }
    if((infile = open(argv[1], O_RDONLY)) == -1)
	{
		printf("mycp: %s: No such file or directory\n", argv[1]);
		exit(0);
	}
	if((outfile = open(argv[2], O_CREAT | O_EXCL | O_WRONLY, 0644)) == -1)
	{
		printf("mycp: %s: Can't create such file\n", argv[2]);
		exit(0);
	}

    copy_file(infile, outfile);

    close(infile);
    close(outfile);
	return 0;
}
