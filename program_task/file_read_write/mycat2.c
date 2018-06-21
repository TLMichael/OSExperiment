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
    return num;
}

int main(int argc, char** argv)
{
    if(argc == 1)
    {
        copy_file(0, 1);
    }
    else
    {
        char *filename;
        int infile;
        for(int i = 1; i < argc; i++)
        {
            filename = argv[i];
            if((infile = open(argv[1], O_RDONLY)) == -1)
            {
                printf("mycat: %s: No such file or directory\n", filename);
                close(infile);
                continue;
            }
            copy_file(infile, 1);
            close(infile);
        }
    }
	return 0;
}
