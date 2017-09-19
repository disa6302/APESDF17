#include <unistd.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>


void main()
{
    int32_t* buf; 
    int32_t* out_buf;
    long retval;
    uint32_t size;
    printf("Enter the size of buffer (upto 256):");
    scanf("%u",&size);
    printf("\n");
    buf = (int32_t *)malloc(size*sizeof(int32_t));
    out_buf = (int32_t *)malloc(size*sizeof(int32_t));
    int i;
    for(i=0;i<size;i++)
    {
	*(buf+i) = rand();
    }

    retval = syscall(333,buf,size,out_buf);
    for(i=0;i<size;i++)
    {
	printf("%i ",*(out_buf+i));
    }

    printf("\n");
    if(retval == 22)
	printf("Invalid Size argument. Provide a size of greater than 0! Sorting exited with status %lu\n\n",retval);
    else if (retval == 14)
	printf("Invalid address access! Sorting exited with status %lu\n",retval);
    else 
	printf("Success! Sorting exited with status %lu\n",retval);
    free(buf);
    free(out_buf);
}
