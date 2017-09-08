
#ifndef __CIRCULARBUFFER_H_INCLUDED
#define __CIRCULARBUFFER_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

struct circularBuffer
{
        uint32_t *head;
        uint32_t *tail;
	uint32_t *base;
        uint32_t size;
        uint32_t num_elements;
};


struct circularBuffer* buffer; 
uint32_t count=0;
uint32_t flag;
uint32_t buffstatusadd = 0;
uint32_t buffstatusdelete = 0;

/*
​ * ​ ​ @brief​ : Enum for Memory allocation and deallocation status
​ *
​ * ​ ​ Returns a code stating the status of allocate and deallocate
 *   MALLOC_FAIL       : Allocation to structure failed
 *   DESTROY_SUCCESS   : Circular Buffer destroyed successfully
 
​ */
enum Status	{MALLOC_FAIL,DESTROY_SUCCESS} status;

/*
​ * ​ ​ @brief​ : Enum to indicate buffer statu
​ *
​ * ​ ​ Returns a code stating the status of buffer
 *   BUFFER_FULL       : Buffer is full,start wrap around
 *   BUFFER_EMPTY      : Buffer is empty, nothing to remove
 
​ */
enum bufferstatus{BUFFER_FULL,BUFFER_EMPTY} bs;

/*
​ * ​ ​ @brief​ : Enum for Operation
​ *
 *   To increment or decrement size depending on add item or delete item operation
​ * ​ ​ Returns a code stating the status of different operations
 *   ADD          : Increment Linked List size
 *   DELETE       : Decrement Linked List size
 *   DISPLAY	  : To display size
​ */
enum Operation	{ADD,DELETE,DISPLAY} operation;

/**
​ * ​ ​ @brief​ : To allocate a buffer
​ *
​ * ​ ​ Returns a status indicating status of allocation
​ * ​ ​
​ *
​ * ​ ​ @param​ ​ cb  ​   A double pointer to the circular buffer structure
​ * ​ ​ @param​ ​ size ​  Size of buffer
​ *
​ * ​ ​ @return​ ​ Errorcode (enum).
​ */
enum Status allocate(struct circularBuffer** cb,uint32_t size);


/**
​ * ​ ​ @brief​ : Add item to the buffer
​ *
​ * ​ ​ Returns a Code stating the status of add item operation
​ * ​ ​
​ *
​ * ​ ​ @param​ ​ cb  ​   A double pointer to the circular buffer structure
​ * ​ ​ @param​ ​ item ​  Item to be added
​ *
​ * ​ ​ @return​ ​ Errrorcode (enum).
​ */

enum bufferstatus add_item(struct circularBuffer** cb,uint32_t item);


/**
​ * ​ ​ @brief​ : Remove item from the buffer
​ *
​ * ​ ​ Returns a Code stating the status of remove item operation
​ * ​ ​
​ *
​ * ​ ​ @param​ ​ cb  ​   A double pointer to the circular buffer structure
​ *
​ * ​ ​ @return​ ​ Errrorcode (enum).
​ */
enum bufferstatus remove_item(struct circularBuffer** cb);

/**
​ * ​ ​ @brief​ : Remove a node from Linked List
​ *
​ * ​ ​ Returns a Code stating the status of remove node operation.
​ * ​ ​
​ *   ​@param​ ​ cb  ​   A double pointer to the circular buffer structure
​ * ​ ​ @return​ ​ None
​ */
void print(struct circularBuffer** cb);

/**
​ * ​ ​ @brief​ : Destroy buffer
​ *
​ * ​ ​ Returns a Code stating the status of remove node operation.
​ *
​ * ​ ​ @return​ ​ None
​ */
enum Status destroy(void);

/**
​ * ​ ​ @brief​ : Check if buffer is full
​ *
​ * ​ ​ Returns a Code stating the buffer full or not full
​ * ​ ​
​ *   ​@param​ ​ cb  ​   A double pointer to the circular buffer structure
​ * ​ ​ @return​ ​ uint32_t
​ */
uint32_t ls_buff_full(struct circularBuffer** cb);

/**
​ * ​ ​ @brief​ : Check if buffer is empty
​ *
​ * ​ ​ Returns a Code stating the buffer is empty or not not empty
​ * ​ ​
​ *   ​@param​ ​ cb  ​   A double pointer to the circular buffer structure
​ * ​ ​ @return​ ​ uint32_t
​ */
uint32_t ls_buff_empty(struct circularBuffer** cb);

/**
​ * ​ ​ @brief​ : Returns size of LinkedList
​ *
​ * ​ ​ Returns size of Linked List
​ *
​ * ​ ​ @return​ ​ uint32_t
​ */
uint32_t size(void);

#endif​ 
