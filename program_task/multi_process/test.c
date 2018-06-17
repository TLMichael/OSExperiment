#include <stdio.h>  
#include <string.h>  
  
int main()  
{  
    char str[] = "echo HELLO WORLD";  
    char delims[] = " ";  
    char *result = NULL;  
    result = strtok( str, delims );  
    while( result != NULL ) 
    {  
        printf( "result is \"%s\"\n", result );  
        result = strtok( NULL, delims );  
    }  
}  
