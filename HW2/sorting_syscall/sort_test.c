/*
* FileName        : 	sort_test.c
* Description     :	A software to utilize the created syscall.
			Appropriate messages are printed according
			to the return from syscall. Size is taken
			from user and care is taken if it does not
			satisfy the boundary conditions

* File Author Name:	Divya Sampath Kumar
* Tools used	  :	gcc
*/

#include <unistd.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>


void input(int32_t* buf,int32_t size)
{
    
    for(int i=0;i<size;i++)
    {
	*(buf+i) = rand();
    }
}


void main()
{
    int32_t* buf; 
    int32_t* out_buf;
    int32_t size;
    int i;
    long retval;

    printf("Enter the size of buffer(>= 256):");
    scanf("%u",&size);
    printf("\n");


    printf("TESTING WITH INVALID INPUT OR OUTPUT BUFFER\n\n");
    buf = (int32_t *)malloc(size*sizeof(int32_t));
    out_buf = (int32_t *)malloc(size*sizeof(int32_t));

    /*Generating an input buffer of random values*/
    input(buf,size);
    
    buf = NULL;
    /*Capturing return value from syscall to print out appropriate messages*/
    retval = syscall(333,buf,size,NULL);

    /*Printing out the sorted buffer*/
    for(i=0;i<size;i++)
    {
        printf("%i ",*(out_buf+i));
    }
    out_buf = NULL;
    printf("\n\n");

    if(retval == 22)
	printf("Invalid Size argument. Provide a size of greater than or equal to 256! Sorting exited with status %lu\n\n",retval);
    else if (retval == 14)
	printf("Invalid address access! Sorting exited with status %lu\n",retval);
    else 
	printf("Success! Sorting exited with status %lu\n",retval);

    free(buf);
    free(out_buf);

    
    printf("TESTING WITH VALID INPUT AND OUTPUT BUFFER\n\n");
    buf = (int32_t *)malloc(size*sizeof(int32_t));
    out_buf = (int32_t *)malloc(size*sizeof(int32_t));

    /*Generating an input buffer of random values*/
    input(buf,size);
    
    /*Capturing return value from syscall to print out appropriate messages*/
    retval = syscall(333,buf,size,out_buf);

    /*Printing out the sorted buffer*/
    for(i=0;i<size;i++)
    {
        printf("%i ",*(out_buf+i));
    }
    printf("\n\n");

    if(retval == 22)
	printf("Invalid Size argument. Provide a size of greater than or equal to 256! Sorting exited with status %lu\n\n",retval);
    else if (retval == 14)
	printf("Invalid address access! Sorting exited with status %lu\n",retval);
    else 
	printf("Success! Sorting exited with status %lu\n",retval);
    
    free(buf);
    free(out_buf);
    printf("\n\n");


}

