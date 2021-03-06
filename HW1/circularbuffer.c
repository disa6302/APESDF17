/*

* FileName        : 	circularbuffer.c
* Description     :	A circular buffer that implements add, remove 
			and takes care of buffer full or empty. If  
			buffer is full, a wrap around is done. Size 
			of buffer can also be obtained.
* File Author Name:	Divya Sampath Kumar
* Tools used	  :	gcc
* Reference	  :	PES Circular Buffer Code
*/



#include<stdio.h>
#include<stdint.h>
#include <stdlib.h>
#include "circularbuffer.h"

/*count              : Indicates current number of items in the buffer*/
uint32_t count=0;

/*flag               : Return a buffer full status if set to 1*/
uint32_t flag = 0;

/*bufferstatusadd    : Stores the status returned by ls_buffer_full function*/
uint32_t buffstatusadd = 0;

/*bufferstatusdelete : Stores the status returned by ls_buffer_empty function*/
uint32_t buffstatusdelete = 0;


enum Status allocate(struct circularBuffer** cb,uint32_t size)
{
    uint32_t* mem;	
    mem = malloc(sizeof(uint8_t)*size);
    struct circularBuffer* memalloc = (struct circularBuffer*)malloc(sizeof(struct circularBuffer));
    if(memalloc == NULL)
    {
        return MALLOC_FAIL;
    }
    memalloc->size = size;
    memalloc->head = mem;
    memalloc->tail = mem;
    memalloc->base = mem;
    *cb = memalloc;
}



enum bufferstatus add_item(struct circularBuffer** cb,uint32_t item)
{
    buffstatusadd = ls_buff_full(cb);	
    if(buffstatusadd==1)
    {
	/*flag: Set when buffer is full-impacts the way buffer is dumped*/
        flag = 1;
	(*cb)->head=(*cb)->base;
	return BUFFER_FULL;		
    }
    *(*cb)->head=item;
     printf("Head in add:%u\n",*(*cb)->head);
    (*cb)->head++;
   
    if((*cb)->num_elements<(*cb)->size)
    {
	(*cb)->num_elements++;
    }
    else (*cb)->num_elements=(*cb)->size;
    return 1;		
}

void print(struct circularBuffer** cb)
{
    /*Keep a copy of Tail, Base and Head pointer*/
    uint32_t* temp_tail;
    uint32_t* temp_base;
    temp_tail = (*cb)->tail;
    temp_base = (*cb)->base;
    printf("Flag value:%u\n",flag);
    if(flag == 1)
    {for(int i=0;i<(*cb)->num_elements;i++)
    {
	printf("%u->",*temp_base);
	temp_base++;
    }}
    else{
    for(int i=0;i<(*cb)->num_elements;i++)
    {
	printf("%u->",*temp_tail);
	temp_tail++;
    }}
    printf("\n");
    if(temp_tail > (*cb)->base+(*cb)->size)
    {
	temp_tail = (*cb)->base;
    }	
}


uint32_t size(struct circularBuffer** cb)
{
    
    return (*cb)->num_elements;
}

uint32_t ls_buff_empty(struct circularBuffer** cb)
{
    printf("Number of elements:%hhu\n",(*cb)->num_elements);
    if((*cb)->num_elements==0)
    {
	return 1;
    }
    else return 0;
}


uint32_t ls_buff_full(struct circularBuffer** cb)
{
    if((*cb)->head >= ((*cb)->base+(*cb)->size))
    {
	return 1;
    }
    else return 0;
}



enum bufferstatus remove_item(struct circularBuffer** cb)
{
    buffstatusdelete = ls_buff_empty(cb);		
    if(buffstatusdelete==1)
    {
	return BUFFER_EMPTY;
    }
    uint8_t item;
    item=*(*cb)->tail;
    printf("\nDeleted item:%d\n",item);
    (*cb)->tail++;
    (*cb)->num_elements--;
    return 0;
    
}

enum Status destroy(struct circularBuffer** cb)
{
    free(*cb);
    return DESTROY_SUCCESS;
}

int main()
{
    struct circularBuffer* buffer = NULL;
    uint32_t item,buffersize,ch;
    printf("Enter the size of buffer to be allocated:");
    scanf("%u",&buffersize);
    status = allocate(&buffer,buffersize);
    if(status == MALLOC_FAIL) 
    {
	printf("Buffer structure could not be allocated\n");
	return;
    }
    printf("Enter your choice(0-5)\n0.Add\n1.Remove\n2.Dump\n3.Get size of list\n4.Delete buffer\n5.Exit\n");
    scanf("%u",&ch);
    while(ch!=5)
    {	
	switch(ch)
	{
 	    case 0: printf("Enter an item:");
   		    scanf("%u",&item);
		    bs = add_item(&buffer,item);
		    if(bs == BUFFER_FULL) 
		    {
			printf("Please select an option to remove an item before adding..Buffer full\n");
	   	    }
		    break;

	    case 1: bs = remove_item(&buffer);
		    if(bs  == BUFFER_EMPTY) 
		    {
			printf("Buffer has nothing in it!Nothing to remove\n");
		    }
		    break;

	    case 2: print(&buffer);
	   	    break;

	    case 3: operation = DISPLAY;
	  	    count=size(&buffer);
		    printf("Number of items:%u\n",count);				
		    break;
	    case 4: status=destroy(&buffer);
	  	    if(status == DESTROY_SUCCESS) printf("Succesfully destroyed\n");
		    break;
	
	    case 5: exit(0);
	}
	if(ch == 4)
	{
	    printf("Enter the size of buffer to be allocated:");
	    scanf("%u",&buffersize);
	    status = allocate(&buffer,buffersize);
	}	
		
	printf("Enter your choice(0-5)\n0.Add\n1.Remove\n2.Dump\n3.Get size of list\n4.Delete buffer\n5.Exit\n");
	scanf("%u",&ch);
    }
}




