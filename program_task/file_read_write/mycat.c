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
	if(argc == 1)
	{
		copy_file(stdin, stdout);
	}
	else
	{
		char *filename;	//
		FILE *infile;
		int count = 0;
		for(int i = 1; i < argc; i++)
		{
			filename = argv[i];
			if((infile = fopen(filename, "r")) == NULL)
			{
				printf("\nmycp: %s: No such file or directory\n", filename);
				continue;
			}
			count++;
			copy_file(infile, stdout);
			fclose(infile);
		}
	}
	return 0;
}
