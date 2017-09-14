#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

void sorting(int32_t* in_buffer, int32_t size, int32_t* sort_buffer);

void sorting(int32_t* in_buffer, int32_t size, int32_t* sort_buffer)
{
    int i,j;
    int32_t temp;
    for(i=0;i<size;i++)
    {
	*(sort_buffer+i) = *(in_buffer+i);
    }
    for(i=0;i<size;i++)
    {
	for(j=i+1;j<size;j++)
	{
	    if(*(sort_buffer+i) < *(sort_buffer+j))
	    {
		temp  = *(sort_buffer+i);
		*(sort_buffer+i) = *(sort_buffer+j);
		*(sort_buffer+j) = temp;
	    }
	}
    }

    printf("Sorted Array:\n");
    for(i=0;i<size;i++)
    {
	printf("%i ",*(sort_buffer+i));
    }
    printf("\n");
}


void main()
{
    int32_t* buf; 
    int32_t* out_buf;
    buf = (int32_t *)malloc(256*sizeof(int32_t));
    out_buf = (int32_t *)malloc(256*sizeof(int32_t));
    int i;
    for(i=0;i<256;i++)
    {
	*(buf+i) = rand();
    }
    sorting(buf,256,out_buf);

}
