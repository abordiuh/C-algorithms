/**
 ******************************************************************************
 *  FILE          : TemplatedLinkedList.h
 *  PROJECT       : PROG8130 Assignment #1
 *  PROGRAMMER    : Artem Bordiuh
 *  CREATED       : 2017-05-25
 *  DESCRIPTION   : Template Linked List header file			
 ******************************************************************************/

#ifndef TEMPLATEDLINKEDLIST_H
#define TEMPLATEDLINKEDLIST_H

#ifdef __cplusplus
extern "C" {
#endif

/*******************************************************************************
 * FOR DETAILED INFORMATION ABOUT TEMPLATE LINKED LIST AND USAGE SEE "TemplateLinkedList.pdf" FILE 
 * ****************************************************************************/

#define TLinkedList(NAME, TYPE) struct NAME {TYPE *data; struct NAME *next; int (*length)();}

#define CreateFuncForTLinkedList(NAMEOFTLL, DATATYPE) \
            void NAMEOFTLL ## _replaceByIndex(NAMEOFTLL **ptrHead, DATATYPE *inData, unsigned int DataIndex) {\
                NAMEOFTLL *ptrCurrentNode = *ptrHead;\
                if (*ptrHead == NULL) {\
                    (*ptrHead) = (NAMEOFTLL*) malloc(sizeof(NAMEOFTLL));\
                    (*ptrHead)->data = NULL;\
                    (*ptrHead)->next = NULL;\
                }\
                ptrCurrentNode = *ptrHead; int indexCounter = 0; while (indexCounter != DataIndex) {\
                    if (ptrCurrentNode->next != NULL) {\
                        ptrCurrentNode = ptrCurrentNode->next;\
                    } else {\
                        ptrCurrentNode->next = (NAMEOFTLL*) malloc(sizeof(NAMEOFTLL));\
                        ptrCurrentNode->next->next = NULL;\
                        ptrCurrentNode = ptrCurrentNode->next;\
                    }\
                    indexCounter++;\
                }\
                if (ptrCurrentNode->data == NULL)\
                    ptrCurrentNode->data = (DATATYPE*) malloc(sizeof (DATATYPE));\
                *(ptrCurrentNode->data) = *inData;\
            }\
            void NAMEOFTLL ## _push (NAMEOFTLL **ptrHead, DATATYPE *inData) {\
              NAMEOFTLL *ptrCurrentNode;\
              if (*ptrHead == NULL) {\
                  *ptrHead = (NAMEOFTLL*) malloc(sizeof (NAMEOFTLL));\
                  (*ptrHead)->next = NULL;\
                  (*ptrHead)->data = (DATATYPE*) malloc(sizeof (DATATYPE));\
                  *((*ptrHead)->data) = *inData;\
                      } else {\
                  ptrCurrentNode = *ptrHead;\
                  while (ptrCurrentNode->next != NULL) {\
                      ptrCurrentNode = ptrCurrentNode->next;\
                              }\
                      ptrCurrentNode->next = (NAMEOFTLL*) malloc(sizeof (NAMEOFTLL));\
                      ptrCurrentNode->next->data = (DATATYPE*) malloc(sizeof (DATATYPE));\
                  *(ptrCurrentNode->next->data) = *inData;\
                  ptrCurrentNode->next->next = NULL;\
              }\
            }

#ifdef __cplusplus
}
#endif

#endif /* TEMPLATEDLINKEDLIST_H */

