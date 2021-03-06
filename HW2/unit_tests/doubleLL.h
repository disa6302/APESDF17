
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
​ * ​ ​ @brief​ ​ An​ ​ abstraction​ ​ for​ ​Double LL Operation
​ *
​ * ​ ​ This​ ​ header​ ​ file​ ​ provides​ ​ an​ ​ abstraction​ ​ of​ ​a double Linked
​ *   List implementation
 *
​ * ​ ​ @author​ ​  Divya Sampath Kumar
​ * ​ ​ @date​ ​    September 19,2017
​ *
​ */

#ifndef CM_DOUBLELL_H
#define CM_DOUBLELL_H

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>


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
 

/**
​ * ​ ​ @brief​ : Structure for LL Node
​ *
​ * ​ ​ Defines structure of a node-every Double LL node has data, pointe to previous and next nodes
​ * ​ ​
​ *
​ * ​ ​ @param​ ​ data  ​ Data at node
​ * ​ ​ @param​ ​ next ​  Address of next Linked List node
​ * ​ ​ @param​ ​ prev ​  Address of previous Linked List node
​ *
​ */

struct Node {
        uint32_t data;
        struct Node* next;
    	struct Node* prev;
};




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
void search(struct Node** head,uint32_t searchVal,uint32_t* position);

/**
​ * ​ ​ @brief​ : Returns size of LinkedList
​ *
​ * ​ ​ Returns size of Linked List
​ *
​ * ​ ​ @return​ ​ uint32_t
​ */
uint32_t size();

#endif // CM_DOUBLELL_H
