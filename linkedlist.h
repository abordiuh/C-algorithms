/**
 ******************************************************************************
 *  FILE          : linkedlist.h
 *  PROJECT       : PROG8130 Assignment #1
 *  PROGRAMMER    : Artem Bordiuh
 *  CREATED       : 2017-05-25
 *  DESCRIPTION   : Ususal Linked List routine			
 ******************************************************************************/

#include <stdio.h>
#include <stdlib.h>


#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#ifdef __cplusplus
extern "C" {
#endif

// Definition of linked list data Node
typedef struct LinkedListNode {
    struct LinkedListNode *ptrNextNode; // pointer to next node in list (NULL if the end)
    char NameData[30]; // the name to be stored (no need to store index)
} LinkedListNodeDef;

// Prototypes
//Function will push new node to the end of the list 
void pushToLinkedList(LinkedListNodeDef **ptrHead, char *NameData);

//Function will push node with data to a linked list by index
//Must start with linked list header pointer. If new pointer created it must be declared as NULL!
//Index count of the data after specified index will be changed by +1 
//*******!!!WARNING!!! If specified index exceed size of a list, empty nodes will be created up to
//*******              specified index (problem solved with a template list)
void pushByIndexToLinkedList(LinkedListNodeDef **ptrHead, char *NameData, unsigned int DataIndex);

//Function will replace node with data in a linked list by index
//Index count will NOT be changed
//******!!!WARNING!!! If specified index exceed size of a list, empty nodes will be created up to
//******              specified index (problem solved with a template list)
void rewriteByIndexToLinkedList(LinkedListNodeDef **ptrHead, char *NameData, unsigned int DataIndex);

//Printing the linked list starting from a header
void printLinkedList(LinkedListNodeDef *ptrHead);


#ifdef __cplusplus
}
#endif

#endif /* LINKEDLIST_H */

