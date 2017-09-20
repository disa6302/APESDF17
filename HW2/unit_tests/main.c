/*
* FileName        : 	doubleLL.c
* Description     :	A double linked list that allows the user to  
			add a node and remove a node from a specific
			index, search a node, return size of list and 
			destroy the list. The list is generated in a
			backward fashion, where the head moves every 
			time a new node is added.
* File Author Name:	Divya Sampath Kumar
* Tools used	  :	gcc
* Reference	  :	https://www.youtube.com/watch?v=LvUgew66zOQ  
*/

#include <stdio.h>
#include <stdlib.h>

#include "doubleLL.h"

int main()
{
    uint32_t *searchIndex;
    uint32_t temp_index;
    searchIndex=&temp_index;
    uint32_t position;
    uint32_t nodeVal;
    uint32_t searchVal;
    uint32_t ch;
    enum Errorcode Errorcode;
    printf("Enter your choice(1-6)\n1.Add Node\n2.Remove Node\n3.Search a node\n4.Get size of list\n5.Destroy LL\n6.Exit\n");
    scanf("%u",&ch);
    while(ch!=6)
    {	
  	switch(ch)
	{
	    case 1: printf("Enter a value:");
    		    scanf("%u",&nodeVal);
		    if(!(head)) Errorcode = add_node(&head,nodeVal,0);
		    else {
		    printf("\nWhat position do you want to add this node to?");
		    scanf("%u",&position);
		    Errorcode = add_node(&head,nodeVal,position);}
		    if(Errorcode == INDEX_OUT_OF_BOUND) 
		    {
			printf("Index out of bound!\n");
			break;
		    }
		    if(Errorcode == ADD_SUCCESS)
		    {
			Print();
			break;
		    }
	    case 2: printf("\nWhat position do you want to remove a node from?");
		    scanf("%u",&position);
		    Errorcode = remove_node(&head,position); 
		    if(Errorcode == INDEX_OUT_OF_BOUND) 
		    {
			printf("Index out of bound!\n");
			break;
		    }
		    if(Errorcode == REMOVE_ERROR)
		    {
			printf("No LL to remove node from\n");
			break;
		    }

		    if(Errorcode == LL_EMPTY)
		    {
	 	 	printf("Linked List Empty..nothing to remove\n");
			break;
		    }
		    if(Errorcode == DELETE_SUCCESS)
		    {
			Print();
			break;
		    }

	    case 3: printf("\nEnter data to be searched for:");
		    scanf("%u",&searchVal);
		    Errocode = search(&head,searchVal,searchIndex);
		    if(*searchIndex == 0)
		    {
			printf("Data not found!\n");
			break;
		    }
		    printf("Data found at %u\n",*searchIndex);
		    break;

	    case 4: printf("\nSize of List:%u\n",value);
	            break;

	    case 5: Errorcode = destroy(&head);
		    if(Errorcode == ERROR_DESTROY)
		    {
			printf("\nLL not available to destroy\n");
			break;
		    }
		    if(Errorcode == DESTROY_SUCCESS)
		    {
			printf("\nLL destroyed\n");
			break;
	   	    }
		
	    case 6: exit(0);
	}
	printf("Enter your choice(1-6)\n1.Add Node\n2.Remove Node\n3.Search a node\n4.Get size of list\n5.Destroy LL\n6.Exit\n");
	scanf("%u",&ch);
    }
}
