/*******************************************************************************
* File Name          : circularQueue.cpp
* Description        : Circular Queue assignment skeleton starting point
*
* Author:			 : Artem Bordiuh
* Revised:           : July 21, 2017
******************************************************************************
*/

#include "stdafx.h"
#include <windows.h>
#include <strsafe.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

DWORD WINAPI myReadThreadFunction(LPVOID lpParam);                                   // function used by read from queue thread
unsigned int putToCircularQueue(char *ptrInputBuffer, unsigned int bufferLength);    // circular queue function to add data to queue
unsigned int getFromCircularQueue(char *ptrOutputBuffer, unsigned int bufferLength); // circular queue function to remove data from queue

#define BUFFER_SIZE         200                // local buffer used for sending or receiving data to/from queue in main and worker thread

#define INPUT_TIMEOUT_MS    5000               // dequeue every 5 seconds

#define CIRCULAR_QUEUE_SIZE 10                // size of the circular queue

// data structure used to keep track of circular queue (DO NOT CHANGE THIS STRUCTURE)
struct myQueueStruct {
	char *ptrBuffer = NULL;                    // pointer to start of the circular queue buffer
	volatile unsigned int queueCount = 0;      // number of characters currently in cirucular queue
	volatile char *ptrCircularHead = NULL;     // location where data is added to queue
	volatile char *ptrCircularTail = NULL;     // loation where data is removed from queue
};

struct myQueueStruct myQueue;							 // create an instance of the circular queue data structure
struct myQueueStruct *myProtectedQueue = &myQueue;       // protection container pointer to a queue

// DO NOT CHANGE THE CODE IN MAIN
int main()
{
	HANDLE  hThread;            // handle to thread
	char    inputBuffer[BUFFER_SIZE];

	myQueue.ptrBuffer = (char *)calloc(CIRCULAR_QUEUE_SIZE, sizeof(char));
	if (myQueue.ptrBuffer == NULL)
	{
		printf("Error unable to allocate memory for buffer\n");
		exit(-1);
	}

	myQueue.ptrCircularHead = myQueue.ptrCircularTail = myQueue.ptrBuffer;

	// create a thread that will consume the data we type in to demonstrate dequeing the data
	hThread = CreateThread(
		NULL,                   // default security attributes
		0,                      // use default stack size  
		myReadThreadFunction,   // thread function name
		NULL,                   // argument to thread function (not being used)
		0,                      // use default creation flags 
		NULL);                  // returns the thread identifier (not being used)

								// get a string from the console and queue it to circular queue
	while (1)
	{
		scanf_s("%s", inputBuffer, BUFFER_SIZE);    // get data from console

													// put the data into the circular queue but check if an error (marked by queue function returning 0) occurred
		if (putToCircularQueue(inputBuffer, strlen(inputBuffer)) == 0)
			printf("Error queuing data\n");
	}
	return 0;
}

// FUNCTION      : putToCircularQueue
// DESCRIPTION   :
//   Put the supplied data into a circular queue
// PARAMETERS    :
//   ptrInputBuffer - a pointer to the buffer to be put into the queue
//   bufferLength   - how many characters are in the buffer being put into the queue
//
// RETURNS       :
//   Number of characters successfully queued (0 on failure)

unsigned int putToCircularQueue(char *ptrInputBuffer, unsigned int bufferLength)
{
	unsigned int numberOfCharsQueued = 0;  // number of characters placed in circular queue
	struct myQueueStruct *protectedQueue = NULL;
	
	while (protectedQueue == NULL) {		//	Wait for myProtectedQueue will be released 
		//Take the myProtectedQueue and block it (possible error can happen if other thread 
		//will interrupt duringt this event)
		protectedQueue = myProtectedQueue;
		myProtectedQueue = NULL;
	}

	if (protectedQueue != NULL)
	{
		// Pointer to the end of queue
		char * queueEndBuffer = protectedQueue->ptrBuffer + (CIRCULAR_QUEUE_SIZE * sizeof(char)) - 1;
		// Iterating through input buffer
		for (int i = 0; i <= bufferLength; i++) {
			// Check if the head reach tail ang queue has data inside 
			if (protectedQueue->ptrCircularTail == protectedQueue->ptrCircularHead && protectedQueue->queueCount != 0) {
				break;
			}
			else {
				/* Check if buffer length exceed so put "end of string" to the stored buffer*/
				if (i == bufferLength) {
					*protectedQueue->ptrCircularTail = '\0';
					protectedQueue->queueCount++;
				}
				else {	// Put data to buffer
					*protectedQueue->ptrCircularTail = *(ptrInputBuffer + i);
					numberOfCharsQueued++;
					protectedQueue->queueCount++;
				} // Iterate tail and if the tail pointer come to queueEndBuffer pointer - start from the queue array begining
				if ((protectedQueue->ptrCircularTail) == queueEndBuffer) {
					protectedQueue->ptrCircularTail = protectedQueue->ptrBuffer;
				}
				else protectedQueue->ptrCircularTail++;
			}
		}
		// Release pointer to a queue
		myProtectedQueue = protectedQueue;
	}
	return numberOfCharsQueued;
}

// FUNCTION      : getFromCircularQueue
// DESCRIPTION   :
//   Read as much data as there is room for from the circular queue
// PARAMETERS    :
//   ptrOutputBuffer - a pointer to the buffer to place the data read from queue
//   bufferLength    - maxiumum number of characters that can be read (IE the size of the output buffer)
//
// RETURNS       :
//   Number of characters successfully queued (0 if none are read)

unsigned int getFromCircularQueue(char *ptrOutputBuffer, unsigned int bufferLength)
{
	unsigned int readCount = 0;
	struct myQueueStruct *protectedQueue = NULL;

	//	Try to grub the queue pointer 
	if (myProtectedQueue != NULL)
	{
		//	Take the myProtectedQueue and block it (possible error can happen if other thread 
		//	will interrupt duringt this event)
		protectedQueue = myProtectedQueue;
		myProtectedQueue = NULL;

		// Pointer to the end of queue
		char * queueEndBuffer = protectedQueue->ptrBuffer + (CIRCULAR_QUEUE_SIZE * sizeof(char)) - 1;

		// Itterate through size of output buffer
		for (int i = 0; i < bufferLength; i++) {
			/* Check if nothing left in a queue and put end of string to the output buffer */
			if (protectedQueue->ptrCircularHead == protectedQueue->ptrCircularTail && protectedQueue->queueCount == 0) {
				*(ptrOutputBuffer + i) = '\0';
				break;
			}
			else {
				/* Check if data which is reading from queue don't reach the end of string */
				if (i + 1 == bufferLength || *protectedQueue->ptrCircularHead == '\0') {
					*(ptrOutputBuffer + i) = '\0';
					protectedQueue->queueCount--;
					if ((protectedQueue->ptrCircularHead) == queueEndBuffer) {
						protectedQueue->ptrCircularHead = protectedQueue->ptrBuffer;
					}
					else protectedQueue->ptrCircularHead++;
					break; //Means data reahced the end of word
				}
				else {
					/* Read data from the queue */
					*(ptrOutputBuffer + i) = *protectedQueue->ptrCircularHead;
					readCount++;
					protectedQueue->queueCount--;
				}
				/* Itterate the queue header */
				if ((protectedQueue->ptrCircularHead) == queueEndBuffer) {
					protectedQueue->ptrCircularHead = protectedQueue->ptrBuffer;
				}
				else protectedQueue->ptrCircularHead++;
			}
		}
		//Release queue pointer, so other threads can access it
		myProtectedQueue = protectedQueue;
	}
	return readCount;
}

// FUNCTION      : myReadThreadFunction
// DESCRIPTION   :
//   A seperate thread from the main program that will independently check for data in queue and print it out
//   DO NOT CHANGE THIS CODE!
// PARAMETERS    :
//   lpParam - arguement passed into thread (not used in this example)
//
// RETURNS       :
//   Will never return so no effective return value

DWORD WINAPI myReadThreadFunction(LPVOID lpParam)
{
	char readBuffer[BUFFER_SIZE];     // local buffer to put the data into when reading from queue and print
	unsigned int  readCount = 0;      // the number of characters read from queue

	while (1)
	{
		Sleep(INPUT_TIMEOUT_MS);      // wait for some data to be received

									  // check if data is available and if so print it out
		readCount = getFromCircularQueue(readBuffer, BUFFER_SIZE);
		if (readCount != 0)           // check for reads that did not get any data
			printf("UNQUEUE: %s\n", readBuffer);
	}
	return 0;    // will never reach here
}


