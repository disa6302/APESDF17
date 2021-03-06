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
#include <stdint.h>
#include "doubleLL.h"

struct Node* head=NULL;


/*value	:	Temporary variable to keep track of number of nodes*/
uint32_t value = 1;

/*flag	:	Set when there is no LL available for performing operations on*/
uint32_t flag=0;

struct Node* getNewNode(uint32_t data)
{
    struct Node* firstNode = (struct Node*)malloc(sizeof(struct Node));
    if(firstNode == NULL)
    {
	printf("MALLOC Error!");
	exit(-1);
    }
    firstNode->data = data;
    firstNode->next = NULL;
    firstNode->prev =  NULL;
    return firstNode;
}


enum Errorcode add_node(struct Node** head,uint32_t val,uint32_t pos)
{
    flag = 0;
    if(pos>=255 || pos >value)
    {
	return INDEX_OUT_OF_BOUND;	
    }
    struct Node* newNode = getNewNode(val); 
    struct Node* nextNode;
    struct Node* temp = *head;

    if(*head == NULL)
    {
        *head = newNode;
        return ADD_SUCCESS;
    }
    if(!(pos))
    {
        (*head)->prev = newNode;
        newNode->next = *head;
	newNode->prev = NULL;
	*head = newNode;
	value ++;
	return ADD_SUCCESS;
    }

    if(pos==value)
    {
        while(temp->next!=NULL)
	{
	     temp = temp->next;
	}
	temp->next = newNode;
	newNode->next = NULL;
	newNode->prev = temp;

	value ++;
	return ADD_SUCCESS;	
    } 
    while(pos!=1)
    {
        temp = temp->next;
        pos--;
    }

    nextNode = temp->next;
    temp->next = newNode;
    newNode->prev = temp;
    newNode->next = nextNode;
    nextNode->prev = newNode;
    value ++;
    return ADD_SUCCESS;	
}

uint32_t size()
{
    return value;
}


void Print() {
    struct Node* temp = head;
    while(temp != NULL) 
    {
   	printf("%d ->",temp->data);
	temp = temp->next;
    }
    printf("\n");
}

enum Errorcode remove_node(struct Node** head,uint32_t pos)
{
    if(pos>=255 || pos >value)
    {
	return INDEX_OUT_OF_BOUND;	
    }
    if(flag == 1)
    {
	return REMOVE_ERROR;
    }
    if(value <=0)
    {
	return LL_EMPTY;
    }
    struct Node* temp = *head;
    struct Node* storeNext;
    struct Node* storePrev;
    if(!(pos))
    {
	*head = (*head)->next;
	(*head)->prev = NULL;
	free (temp);
	/*Operation = DELETE;
	value = size();*/
	value --;
	return DELETE_SUCCESS;	
    }
    if(pos == value)
    {
 	storeNext = *head;
	if(temp == NULL) return LL_EMPTY;
	while(temp->next!=NULL)
	{
       	    temp=temp->next;
	}
	storeNext = temp->prev;
	storeNext->next = NULL;
	free(temp);
	/*Operation = DELETE;
	value = size();*/
	value --;
	return DELETE_SUCCESS;
    }
    while(pos!=0)
    {
 	temp = temp->next;
 	pos--;
    }
    storeNext = temp->next;
    storePrev = temp->prev;
    storeNext->prev = storePrev;
    storePrev->next =  storeNext;
    /*Operation = DELETE;
	value = size();*/
    value --;
    free(temp);
    return DELETE_SUCCESS;
}



void search(struct Node** head,uint32_t searchVal,uint32_t* position)
{	

    struct Node* searching = *head;
    uint32_t *pos = malloc(sizeof(pos));
    *pos = 1;
    while(searching!= NULL)
    {
	if(searching->data == searchVal)
	{
            *position = *pos;
	}
	searching = searching->next;
	(*pos)++;
    }
    free(pos);

}

enum Errorcode destroy(struct Node** head)
{
    if(value == 0)
    {
        return ERROR_DESTROY;
    }	
    struct Node* present = *head;
    struct Node* next;
    while(present!=NULL)
    {
	next = present->next;
	free(present);
	present = next;
    }
    *head = NULL;
    value = 0;
    flag = 1;
    return DESTROY_SUCCESS;
}

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
			    search(&head,searchVal,searchIndex);
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
