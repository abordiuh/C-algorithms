/**
 ******************************************************************************
 *  FILE          : linkedlist.c
 *  PROJECT       : PROG8130 Assignment #1
 *  PROGRAMMER    : Artem Bordiuh
 *  CREATED       : 2017-05-25
 *  DESCRIPTION   : Ususal Linked List routine			
 ******************************************************************************/

#include "linkedlist.h"

//Function will push node with data to a linked list by index
//Must start with linked list header pointer. If new pointer created it must be declared as NULL!
//Index count of the data after specified index will be changed by +1 
//  !!!WARNING!!! If specified index exceed size of a list, empty nodes will be created up to
//                  specified index (problem solved with a template list)
void pushByIndexToLinkedList(LinkedListNodeDef **ptrHead, char *NameData, unsigned int DataIndex) {
    //Initializing temporary nodes to iterate through linked list
    LinkedListNodeDef *ptrCurrentNode = *ptrHead;
    LinkedListNodeDef *ptrPreviousNode = NULL;

    //Initializing header node if empty
    if (*ptrHead == NULL) {
        *ptrHead = (LinkedListNodeDef*) malloc(sizeof (LinkedListNodeDef));
        (*ptrHead)->ptrNextNode = NULL;
    }
    
    //Iterating through nodes and initializing empty ones if specified index exceed
    //overall count of nodes
    ptrCurrentNode = *ptrHead;
    int indexCounter = 0;
    while (indexCounter != DataIndex) {
        if (ptrCurrentNode->ptrNextNode != NULL) {
            ptrPreviousNode = ptrCurrentNode;
            ptrCurrentNode = ptrCurrentNode->ptrNextNode;
        } else {
            ptrPreviousNode = ptrCurrentNode;
            ptrCurrentNode->ptrNextNode = (LinkedListNodeDef*) malloc(sizeof (LinkedListNodeDef));
            ptrCurrentNode->ptrNextNode->ptrNextNode = NULL;
            ptrCurrentNode = ptrCurrentNode->ptrNextNode;
        }
        indexCounter++;
    }

    //adding new node on the place of specified index (so overall nodes count change
    // since following nodes will be theoretically pushed)
    if (indexCounter != 0) {
        LinkedListNodeDef* ptrInsertingNode = (LinkedListNodeDef*) malloc(sizeof (LinkedListNodeDef));
        ptrInsertingNode->ptrNextNode = ptrCurrentNode;
        ptrPreviousNode->ptrNextNode = ptrInsertingNode;
        sprintf((ptrInsertingNode)->NameData, "%s", NameData);
    } else if (indexCounter == 0) {
        LinkedListNodeDef* ptrInsertingNode = (LinkedListNodeDef*) malloc(sizeof (LinkedListNodeDef));
        ptrInsertingNode->ptrNextNode = ptrCurrentNode;
        *ptrHead = ptrInsertingNode;
        sprintf((ptrInsertingNode)->NameData, "%s", NameData);
    }
}

//Function will replace node with data in a linked list by index
//Index count will NOT be changed
//  !!!WARNING!!! If specified index exceed size of a list, empty nodes will be created up to
//                  specified index (problem solved with a template list)
void rewriteByIndexToLinkedList(LinkedListNodeDef **ptrHead, char *NameData, unsigned int DataIndex){
    //Initializing current position pointer and header if null
    LinkedListNodeDef *ptrCurrentNode = *ptrHead;
    if (*ptrHead == NULL) {
        *ptrHead = (LinkedListNodeDef*) malloc(sizeof (LinkedListNodeDef));
        (*ptrHead)->ptrNextNode = NULL;
    }
    
    //Going through list of nodes        
    ptrCurrentNode = *ptrHead;
    int indexCounter = 0;
    while (indexCounter != DataIndex) {
        if (ptrCurrentNode->ptrNextNode != NULL) {
           ptrCurrentNode = ptrCurrentNode->ptrNextNode;
        } else {
            ptrCurrentNode->ptrNextNode = (LinkedListNodeDef*) malloc(sizeof (LinkedListNodeDef));
            ptrCurrentNode->ptrNextNode->ptrNextNode = NULL;
            ptrCurrentNode = ptrCurrentNode->ptrNextNode;
        }
        indexCounter++;
    }
        //replacing data of the node in the specified position
        sprintf((ptrCurrentNode)->NameData, "%s", NameData);
}

//Function will push new node to the end of the list 
void pushToLinkedList(LinkedListNodeDef **ptrHead, char *NameData) {
    //Initializing current position pointer 
    LinkedListNodeDef *ptrCurrentNode;
    
    //Initializing header if null and pushing new node
    if (*ptrHead == NULL) {
        *ptrHead = (LinkedListNodeDef*) malloc(sizeof (LinkedListNodeDef));
        (*ptrHead)->ptrNextNode = NULL;
        sprintf((*ptrHead)->NameData, "%s", NameData);
    } else {// if header present iterating through list of nodes to the end
        ptrCurrentNode = *ptrHead;
        while (ptrCurrentNode->ptrNextNode != NULL) {
            ptrCurrentNode = ptrCurrentNode->ptrNextNode;
        }
        //allocating space to a new node and pushing it to the end of linked list 
        ptrCurrentNode->ptrNextNode = (LinkedListNodeDef*) malloc(sizeof (LinkedListNodeDef));
        sprintf(ptrCurrentNode->ptrNextNode->NameData, "%s", NameData);
        ptrCurrentNode->ptrNextNode->ptrNextNode = NULL;
    }
}

// Print out the linked list starting at the supplied linked list head
void printLinkedList(LinkedListNodeDef *ptrHead) {
    if(ptrHead == NULL){
        printf("LINKED LIST IS EMPTY\n\r"); 
        return;
    }
    LinkedListNodeDef *ptrCurrentNode = ptrHead;
    int indexCounter = 0;
    while (ptrCurrentNode != NULL) {
        printf("Node %d: %s\r\n", indexCounter, ptrCurrentNode->NameData);
        ptrCurrentNode = ptrCurrentNode->ptrNextNode;
        indexCounter++;
    }
}