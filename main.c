/**
 ******************************************************************************
 *  FILE          : main.c
 *  PROJECT       : PROG8130 Assignment #1
 *  PROGRAMMER    : Artem Bordiuh
 *  CREATED       : 2017-05-25
 *  DESCRIPTION   : Examples of Linked Lists and Template Linked List			
 ******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include "linkedlist.h"
#include "TemplatedLinkedList.h"

// make the data positions the last 5 digits of student number
// student number - 73916

// structure/typedef used for holding data
typedef struct InputDataStruct {
    char name[30];
    int index;
} InputData;

// data used for test
InputData iData[5] = {
    { "Dog", 7},
    { "Cat", 3},
    { "Turtle", 9},
    { "Fish", 1},
    { "Bird", 6}
};

typedef TLinkedList(MyNodeName_ForInt, int) MyTLinkListInt;
CreateFuncForTLinkedList(MyTLinkListInt, int);

void printMyListInt(MyTLinkListInt **head) {
    MyTLinkListInt *ptrCurrentNode = *head;
    int indexCounter = 0;
    while (ptrCurrentNode != NULL) {
        if (ptrCurrentNode->data != NULL)
            printf("Node %d: %d\r\n", indexCounter, *(ptrCurrentNode->data));
        ptrCurrentNode = ptrCurrentNode->next;
        indexCounter++;
    }
}

typedef TLinkedList(MyNodeName_ForStruct, InputData) MyTLinkListStruct;
CreateFuncForTLinkedList(MyTLinkListStruct, InputData);

void printMyListStruct(MyTLinkListStruct **head) {
    MyTLinkListStruct *ptrCurrentNode = *head;
    int indexCounter = 0;
    while (ptrCurrentNode != NULL) {
        if (ptrCurrentNode->data != NULL)
            printf("Node %d: %s\r\n", indexCounter, (ptrCurrentNode->data)->name);
        else
            printf("Node %d: (Here is null, no space allocated)\r\n", indexCounter);
        ptrCurrentNode = ptrCurrentNode->next;
        indexCounter++;
    }
}

void main(void) {
    int i;

    // define linked list head
    static LinkedListNodeDef *ptrHead = NULL;
    static LinkedListNodeDef *ptrHeadSorted1 = NULL;
    static LinkedListNodeDef *ptrHeadSorted2 = NULL;

    // Print out the input data
    printf("Data before Linked List is:\n\r");
    for (i = 0; i < 5; i++)
        printf("%s , %d\n", iData[i].name, iData[i].index);

    // insert the data into Linked List to the end
    for (i = 0; i < 5; i++)
        pushToLinkedList(&ptrHead, iData[i].name);

    // now print out the list in order it is stored starting at head
    printf("\nData in the NOT SORTED Linked List is:\n\r");
    printLinkedList(ptrHead);

    // insert the data into Linked List by indexes, but indexes will be MOVED
    for (i = 0; i < 5; i++)
        pushByIndexToLinkedList(&ptrHeadSorted1, iData[i].name, iData[i].index);

    printf("\nData pushed by indexes in the SORTED Linked List is:\n\r");
    printLinkedList(ptrHeadSorted1);

    // insert the data into Linked List by indexes, but data will be REWROTE
    for (i = 0; i < 5; i++)
        rewriteByIndexToLinkedList(&ptrHeadSorted2, iData[i].name, iData[i].index);

    printf("\nData which rewrote previous by indexes in the SORTED Linked List is:\n\r");
    printLinkedList(ptrHeadSorted2);

    //It is a template linked list example with type int as data
    printf("\nNow template linked list with int as a datatype (push to the end)\n\r");
    MyTLinkListInt *myTListS = NULL;
    // Insert the data into Linked List to the end
    for (i = 0; i < 5; i++) {
        MyTLinkListInt_push(&myTListS, &(iData[i].index));
    }
    printMyListInt(&myTListS);

    //It is a template linked list example with type struct InputData as data
    printf("\nNow template linked list with struct InputData as a datatype (replace by index)\n\r");
    MyTLinkListStruct *myTListI = NULL;
    // insert the data into Linked List by indexes
    for (i = 0; i < 5; i++) {
        MyTLinkListStruct_replaceByIndex(&myTListI, &iData[i], iData[i].index);
    }
    printMyListStruct(&myTListI);

    //Not sure if it's very helpful but I will leave it here:
    free(ptrHead);
    free(ptrHeadSorted1);
    free(ptrHeadSorted2);
    free(myTListS);
    free(myTListI);
}
