#include<stdio.h>
#include<stdint.h>
#include <stdlib.h>
#include "circularbuffer.h"


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
		uint8_t flag;
		if(buffstatusadd==1)
		{
			flag = 1;
			(*cb)->num_elements=0;
			(*cb)->head=(*cb)->base;		

		}
		*(*cb)->head=item;
		(*cb)->head++;
		operation = ADD;
		count = size();
		//printf("%hhu",*(*cb)->base);
		if(flag == 1)
		{
			return BUFFER_FULL;
		}
		
}

void print(struct circularBuffer** cb)
{
	uint32_t* temp;
	temp = (*cb)->tail;
	if(temp <= (*cb)->head)
	{
		while(temp!=(*cb)->head)	
		{
			printf("%hhu->",*temp);
			temp++;
		}
	}
	printf("\n");
}


uint32_t size()
{
	if(operation==DELETE)
	{
		buffer->num_elements--;
		return buffer->num_elements;
	}
	if(operation==ADD)
	{
		buffer->num_elements++;
		return buffer->num_elements;
	}
	if(operation == DISPLAY)
	return buffer->num_elements;
}

uint32_t ls_buff_empty(struct circularBuffer** cb)
{
	printf("Number of elements:%hhu\n",(*cb)->num_elements);
	if((*cb)->num_elements==0)
	{
		printf("entered..\n");
		return 1;
	}
	else return 0;
	
}


uint32_t ls_buff_full(struct circularBuffer** cb)
{
	
	if((*cb)->num_elements == (*cb)->size)
	{
		return 1;
	}
	else return 0;

}



enum bufferstatus remove_item(struct circularBuffer** cb)
{
	buffstatusdelete = ls_buff_empty(cb);
	printf("Buffer Empty:%hhu",buffstatusdelete);		
	if(buffstatusdelete==1)
	{
		return BUFFER_EMPTY;
	}
	uint8_t item;
	item=*(*cb)->tail;
	printf("\nDeleted item:%d\n",item);
	(*cb)->tail++;
	operation = DELETE;
	count = size();
}

enum Status destroy()
{
	free(buffer);
	return DESTROY_SUCCESS;
}

void main()
{

	uint32_t item,buffersize,ch;
	printf("Enter the size of buffer to be allocated:");
	scanf("%u",&buffersize);
	status = allocate(&buffer,buffersize);

	if(status == MALLOC_FAIL) 
	{
		printf("Buffer structure could not be allocated\n");
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
					printf("Wrap around occured...print to see new buffer\n");
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
				count=size();
				printf("Number of items:%u",count);				
				break;
			case 4: status=destroy();
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




