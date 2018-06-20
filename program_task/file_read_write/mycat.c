#include<stdio.h>
#include<fcntl.h>

int copy_file(FILE *src, FILE *dest)
{
	int c;
	while((c = getc(src)) != EOF)
		putc(c, dest);
	return c;
}

int main(int argc, char** argv)
{
	if(argc == 1)
	{
		copy_file(stdin, stdout);
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
				continue;
			}
			copy_file(infile, stdout);
			fclose(infile);
		}
	}
	return 0;
}
