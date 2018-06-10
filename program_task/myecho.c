#include<stdio.h>

int main(int argc, char** argv)
{
//	printf("argc: %d\n", argc);
//	for(int i=0; i<argc; i++)
//	{
//		printf("[%d]: %s\n", i, argv[i]);
//	}
	int i;
	for(i = 1; i < argc - 1; i++)
	{
		printf("%s ", argv[i]);
	}
	if(argc > 1)	
		printf("%s\n", argv[i]);
	

	return 0;
}
