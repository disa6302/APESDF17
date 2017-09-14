#include <unistd.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

#define SIZE 256

void main()
{
    int32_t* buf; 
    int32_t* out_buf;
    long retval;
    
    buf = (int32_t *)malloc(SIZE*sizeof(int32_t));
    out_buf = (int32_t *)malloc(SIZE*sizeof(int32_t));
    int i;
    
    for(i=0;i<SIZE;i++)
    {
	*(buf+i) = rand();
    }
    
    retval = syscall(333,buf,SIZE,out_buf);
    printf("Sorting exited with status (0=Success else error):%lu\n",retval);
    for(i=0;i<SIZE;i++)
    {
	printf("%i ",*(out_buf+i));
    }
    printf("\n");
}
