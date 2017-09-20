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

#include <stdint.h>
#include <math.h>
#include <stdlib.h>
#include "doubleLL.h"

struct Node* head=NULL;

/*value	   :	Temporary variable to keep track of number of nodes*/
uint32_t value = 1;

/*flag	   :	Set when there is no LL available for performing operations on*/
uint32_t flag=0;

/*rem_node :To check if remove operation is performed on an empty LL*/
uint32_t rem_node=0;

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
    rem_node = 1;
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
	value++;
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
	value++;
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
    value++;
    return ADD_SUCCESS;	
}

uint32_t size()
{
    return value;
}

enum Errorcode remove_node(struct Node** head,uint32_t pos)
{
    if(rem_node==0)
    {
	return LL_EMPTY;
    }
    else if(pos>=255 || pos >value)
    {
	return INDEX_OUT_OF_BOUND;	
    }
    else if(flag == 1)
    {
	return REMOVE_ERROR;
    }

    struct Node* temp = *head;
    struct Node* storeNext;
    struct Node* storePrev;
    if(!(pos))
    {
	*head = (*head)->next;
	(*head)->prev = NULL;
	free (temp);
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
