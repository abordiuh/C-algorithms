/*******************************************************************************
* File Name          : hashAssignment.cpp
* Description        : Implemenation of a hash skelleton
*
* Author:              PROG8130 / Artem Bordiuh
* Date:                August 10, 2017
******************************************************************************
*/

#include "stdafx.h"
#include <stdlib.h>
#include <windows.h>
#include <strsafe.h>


unsigned int putIntoHashTable(char *ptrInputData, unsigned int bufferLength);    // function to add to has-h table
unsigned int getFromHashTable(char *ptrOutputData, unsigned int bufferLength);   // function to retrieve data from hash table

#define INPUT_BUFFER_SIZE         200             // local buffer used for adding to hash table

#define HASH_SIZE    3                          // size of hash table to be used

																				 // data structure used to keep track of hashed data
struct myHashStruct {
	char *ptrBuffer = NULL;                       // pointer to data stored in hash
	struct myHashStruct *ptrNextHashData = NULL;  // pointer to next item in this hash bucket (or NULL if no more)
};

struct myHashStruct *myHash[HASH_SIZE];             // create an empty hash table structure

int main()
{
	char    inputBuffer[INPUT_BUFFER_SIZE];

	// initialize the hash table to empty one
	for (int i = 0; i < HASH_SIZE; i++)
	{
		if ((myHash[i] = (struct myHashStruct *) calloc(1, sizeof(struct myHashStruct))) == NULL)
		{
			printf("calloc failed!\n");
			exit(-1);
		}
	}

	// add to hash table loop
	while (1)
	{
		printf("enter data to be added to hash table or exit when done\n");

		// get strings from the console and place in hash until nothing entered
		scanf_s("%s", inputBuffer, INPUT_BUFFER_SIZE);

		// stop adding data into hash table when "exit" is entered
		if (strcmp(inputBuffer, "exit") == 0)
			break;

		if (putIntoHashTable(inputBuffer, strlen(inputBuffer)) == HASH_SIZE)
			printf("Error putting into hash table\n");
	}

	// check if data is in hash table
	while (1)
	{
		unsigned int hashIndexNumber = 0;

		printf("Enter data to find, done when complete\n");

		// get strings from the console and check if in hash table
		scanf_s("%s", inputBuffer, INPUT_BUFFER_SIZE);

		// stop adding data into hash table when "done" is entered
		if (strcmp(inputBuffer, "done") == 0)
			break;

		if ((hashIndexNumber = getFromHashTable(inputBuffer, strlen(inputBuffer))) == HASH_SIZE)
			printf("%s not found in hash table\n", inputBuffer);
		else
			printf("%s found in hash table at %u\n", inputBuffer, hashIndexNumber);
	}

	return 0;
}

// FUNCTION      : myHashFunction
// DESCRIPTION   :
//   Calculate a hash value to use in storing the data into the hash table
// PARAMETERS    :
//   ptrInputBuffer - a pointer to the buffer to be put into the hash table
//
// RETURNS       :
//   Hash value calculated ( HASH_SIZE on failure)

unsigned int myHashFunction(char *ptrInputBuffer)
{
	unsigned int calculatedHashValue = 0;
	
	//Sum of each char multiplied by it position number
	for (int i = 0; i < strlen(ptrInputBuffer); i++) {
		calculatedHashValue = calculatedHashValue + (*(ptrInputBuffer + i) * i);
	}

	// make sure if hash value is bigger than the table size, the value wraps
	return calculatedHashValue%HASH_SIZE;
}

// FUNCTION      : putIntoHashTable
// DESCRIPTION   :
//   Put the supplied data into a hash table
// PARAMETERS    :
//   ptrInputBuffer - a pointer to the buffer to be put into the hash table
//   bufferLength   - how many characters are in the buffer being put into the hash table
//
// RETURNS       :
//   Hash value used ( HASH_SIZE on failure)

unsigned int putIntoHashTable(char *ptrInputData, unsigned int bufferLength)
{
	unsigned int hashValue = myHashFunction(ptrInputData);

	// if not null then check if the value is in the hash, strncmp - null terminated
	if (myHash[hashValue]->ptrBuffer != NULL 
		&& (strncmp(myHash[hashValue]->ptrBuffer, ptrInputData, strlen(ptrInputData)) == 0))
		return HASH_SIZE;

	//Creating hash node and allocating memory for its data, storing data
	struct myHashStruct hashNode;
	if ((hashNode.ptrBuffer = (char *)malloc(strlen(ptrInputData))) == NULL) {
		printf("Error when allocating memory!\n");
		exit(-1);
	}
	sprintf(hashNode.ptrBuffer, "%s", ptrInputData);
	 
	//Checking if nothing yet in the bucket
	if (myHash[hashValue]->ptrBuffer == NULL) {
		*myHash[hashValue] = hashNode;
		myHash[hashValue]->ptrNextHashData = NULL;
		return hashValue;
	}
		
	//Look for next free slot in the bucket
	struct myHashStruct *tmpHashStructPointer = myHash[hashValue];
	while (tmpHashStructPointer->ptrNextHashData != NULL) {
		tmpHashStructPointer = tmpHashStructPointer->ptrNextHashData;
	}//Till this point we reach end of bucket list
	
	//Putting data to free place
	if ((tmpHashStructPointer->ptrNextHashData = (struct myHashStruct *) malloc(sizeof(struct myHashStruct))) == NULL)
	{
		printf("Error when allocating memory!\n");
		exit(-1);
	}
	*tmpHashStructPointer->ptrNextHashData = hashNode;

	return hashValue;
}

// FUNCTION      : getFromHashTable
// DESCRIPTION   :
//   Read as much data as there is room for from the hash table
// PARAMETERS    :
//   ptrOutputBuffer - a pointer to the buffer to place the data read from hash table
//   bufferLength    - maxiumum number of characters that can be read
//
// RETURNS       :
//   Hash value used ( HASH_SIZE on failure)

unsigned int getFromHashTable(char *ptrOutputData, unsigned int bufferLength)
{
	unsigned int hashValue = myHashFunction(ptrOutputData);

	if (myHash[hashValue]->ptrBuffer != NULL && ptrOutputData != NULL) {
		
		struct myHashStruct *pHashNode = myHash[hashValue];
		//CHecking if the string in the bucket
		while (pHashNode!= NULL && pHashNode->ptrBuffer != NULL){
			if (strncmp(pHashNode->ptrBuffer, ptrOutputData, strlen(ptrOutputData)) == 0) {
				return hashValue;
			}
			pHashNode = pHashNode->ptrNextHashData;
		}

		// Here is not a dead code. It's another possible implementation for copying everything from bucket 
		// till output buffer is full

		/*	
		//cleaning buffer
		memset(ptrOutputData, 0, bufferLength);

		struct myHashStruct *tmpHashStructPointer = myHash[hashValue];
		int bufferPosition = 0;

		while (tmpHashStructPointer != NULL) {
			if ((strlen(tmpHashStructPointer->ptrBuffer) + bufferPosition) < bufferLength-2) { 
				//bufferLength-2 is because we will 3 more characters at the end if available
				
				strcat(ptrOutputData, tmpHashStructPointer->ptrBuffer);
				bufferPosition += strlen(tmpHashStructPointer->ptrBuffer);
			}
			else {
				if(bufferPosition!=0)
					strcat(ptrOutputData, " ");
				memcpy(ptrOutputData + bufferPosition, tmpHashStructPointer->ptrBuffer, bufferLength - bufferPosition);
			}

			tmpHashStructPointer = tmpHashStructPointer->ptrNextHashData;
		}//Till this point we reach end of bucket list	
		
		return hashValue;
	*/
	}
	//Here nothing found in hesh table
	return HASH_SIZE;
}

// end code *    *        