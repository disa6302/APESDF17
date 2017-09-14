#include <unistd.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#define SIZE 10

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
    syscall(333,buf,SIZE,out_buf);

    for(i=0;i<SIZE;i++)
    {
	printf("%i ",*(out_buf+i));
    }
    //syscall(333, "Testing the sort syscall");
}
