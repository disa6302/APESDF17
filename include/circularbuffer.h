
/**********************************************************************************************
​ * ​ ​ Copyright​ ​ (C)​ ​ 2017​ ​ by​ ​ Divya Sampath Kumar
​ *
​ * ​ ​ Redistribution,​ ​ modification​ ​ or​ ​ use​ ​ of​ ​ this​ ​ software​ ​ in​ ​ source​ ​ or​ ​ binary
​ * ​ ​ forms​ ​ is​ ​ permitted​ ​ as​ ​ long​ ​ as​ ​ the​ ​ files​ ​ maintain​ ​ this​ ​ copyright.​ ​ Users​ ​ are
​ * ​ ​ permitted​ ​ to​ ​ modify​ ​ this​ ​ and​ ​ use​ ​ it​ ​ to​ ​ learn​ ​ about​ ​ the​ ​ field​ ​ of​ ​ embedded
​ * ​ ​ software.​ ​ Alex​ ​ Fosdick​ ​ and​ ​ the​ ​ University​ ​ of​ ​ Colorado​ ​ are​ ​ not​ ​ liable​ ​ for
​ * ​ ​ any​ ​ misuse​ ​ of​ ​ this​ ​ material.
​ *
***********************************************************************************************/
/**
​ * ​ ​ @file​ ​ doubleLL.h
​ * ​ ​ @brief​ ​ An​ ​ abstraction​ ​ for​ Circular Buffer Operation
​ *
​ * ​ ​ This​ ​ header​ ​ file​ ​ provides​ ​ an​ ​ abstraction​ ​ of​ ​a Circular Buffer
 *   implementation
 *
​ * ​ ​ @author​ ​  Divya Sampath Kumar
​ * ​ ​ @date​ ​    September 8,2017
​ *
​ */
#ifndef __CIRCULARBUFFER_H_INCLUDED
#define __CIRCULARBUFFER_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

/**
​ * ​ ​ @brief​ : Structure for Circular buffer
​ *
​ * ​ ​ Defines structure of a circular buffer-every buffer will have a 
 *   head, tail and base pointer. Base pointer is constant, head is  ​ ​ 
​ *   incremented on adding an element and tai on removing an element
 *
​ * ​ ​ @param​ ​ head  ​         Head pointer
​ * ​ ​ @param​ ​ tail           Tail Pointer
​ * ​ ​ @param​ ​ base ​          Base Pointer
​ *   @param​ ​ size ​          Max size of buffer
 *   @param​ ​ num_elements ​  Number of elements in buffer
 *
​ */

struct circularBuffer
{
        uint32_t *head;
        uint32_t *tail;
	uint32_t *base;
        uint32_t size;
        uint32_t num_elements;
};




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
enum Status destroy(struct circularBuffer** cb);

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
 *   ​@param​ ​ cb  ​   A double pointer to the circular buffer structure
​ * ​ ​ @return​ ​ uint32_t
​ */
uint32_t size(struct circularBuffer** cb);

#endif​ //__CIRCULARBUFFER_H_INCLUDED
