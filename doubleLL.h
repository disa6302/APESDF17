
#ifndef __DOUBLELL_H_INCLUDED
#define __DOUBLELL_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

/*
​ * ​ ​ @brief​ : Enum for ErrorCode
​ *
​ * ​ ​ Returns a code stating the status of different operations:
 *   ADD_SUCCESS       : Successful Add opeartion
 *   INDEX_OUT_OF_BOUND: When operation attempts to access an index out of bound
 *   DELETE_SUCCESS    : Delete operation successful
 *   LL_EMPTY           : Linked List Empty
​ * ​ ​ DESTROY_SUCCESS   : Linked List successfully destroyed
​ *   ERROR_DESTROY     : No Linked List available to destroy
​ */
enum Errorcode  {ADD_SUCCESS,INDEX_OUT_OF_BOUND,DELETE_SUCCESS,LL_EMPTY,DESTROY_SUCCESS,ERROR_DESTROY,REMOVE_ERROR};

/*
​ * ​ ​ @brief​ : Enum for Operation
​ *
 *   To increment or decrement size depending on add node or delete node operation
​ * ​ ​ Returns a code stating the status of different operations:
 *   ADD       : Increment Linked List size
 *   DELETE    : Decrement Linked List size
​ */
enum Operation  {ADD,DELETE} Operation;
 

struct Node {
        uint32_t data;
        struct Node* next;
    	struct Node* prev;
};

struct Node* head;
uint32_t count = 1;
uint32_t value;
uint32_t flag=0;

/**
​ * ​ ​ @brief​ : Adds a node to the linked list
​ *
​ * ​ ​ Returns a code stating the status of add operation.
​ * ​ ​
​ *
​ * ​ ​ @param​ ​ head  ​ A double pointer to the head of the Linked List
​ * ​ ​ @param​ ​ val​ ​   Data to be added to the Linked List
​ * ​ ​ @param​ ​ pos ​   Position where data is to be added
​ *
​ * ​ ​ @return​ ​ Errorcode (enum).
​ */
enum Errorcode add_node(struct Node** head,uint32_t val,uint32_t pos);

/**
​ * ​ ​ @brief​ : Remove a node from Linked List
​ *
​ * ​ ​ Returns a Code stating the status of remove node operation.
​ * ​ ​
​ *
​ * ​ ​ @param​ ​ head  ​ A double pointer to the head of the Linked List
​ * ​ ​ @param​ ​ pos ​   Position from where data is to be removed
​ *
​ * ​ ​ @return​ ​ Errorcode (enum).
​ */
enum Errorcode remove_node(struct Node** head,uint32_t pos);


/**
​ * ​ ​ @brief​ : Removes the Linked List from memory
​ *
​ * ​ ​ Returns a Code stating the status of destroy operation
​ * ​ ​
​ *
​ * ​ ​ @param​ ​ head  ​ A double pointer to the head of the Linked List

​ *
​ * ​ ​ @return​ ​ Errorcode (enum).
​ */
enum Errorcode destroy(struct Node** head);

/**
​ * ​ ​ @brief​ : Display inked List at every step
​ *
​ */
void ReversePrint();

/**
​ * ​ ​ @brief​ : Create new node
​ *
 *   Creates a new node in the list
 *
 *   @param​ ​ data ​  Data to be added
​ */
struct Node* getNewNode(uint32_t data);

/**
​ * ​ ​ @brief​ : Search a node to the linked list
​ *
​ * ​ ​ Returns the position of the node in the Linked List
​ * ​ ​
​ *
​ * ​ ​ @param​ ​ head  ​     A double pointer to the head of the Linked List
​ * ​ ​ @param​ ​ searchVal​ ​ Data to be searched for in the list
=
​ *
​ * ​ ​ @return​ ​ pointer to position.
​ */
uint32_t * search(struct Node** head,uint32_t searchVal);

/**
​ * ​ ​ @brief​ : Returns size of LinkedList
​ *
​ * ​ ​ Returns size of Linked List
​ *
​ * ​ ​ @return​ ​ uint32_t
​ */
uint32_t size();

//__DOUBLELL_H_INCLUDED
#endif​ 
