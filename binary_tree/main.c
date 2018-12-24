/**
 ******************************************************************************
 *  FILE          : main.c
 *  PROJECT       : Binary tree
 *  PROGRAMMER    : Artem Bordiuh
 *  FIRST VERSION : 2017-06-14
 *  DESCRIPTION   : Implementation of binary tree with recursive alphabetical 
					information insert, depth first and breath free traversals
 *****************************************************************************
 **/
 
#include <stdio.h>
#include "bintree.h"
#include <time.h>

/* Size of data structure with strings to fill binary tree withb */
#define INPUT_DATA_SIZE 7

//Data to be stored in the binary tree
InputData inData[INPUT_DATA_SIZE] = {
    { "allan"},
    { "jaswinder"},
    { "zelda"},
    { "tony"},
    { "gunder"},
    { "misty"},
    {"artem"}
};

/**
 * @brief  Putting data to the binary tree and using different traversals to
 * 		   display it.
 */
int main() {
	/* Clock used for measuring time of binary tree routine */
    clock_t begin = clock();
    TreeNode* head = NULL; // Header
    // Put all the data into the binary tree
    for (int i = 0; i < INPUT_DATA_SIZE; i++)
        addToBinaryTree_AlphbSort(createNewNode(inData[i].name), &head);
    clock_t end = clock();
    printf("Time of adding %d strings to bin tree %.3f msec\n", INPUT_DATA_SIZE, (double) (end - begin) / CLOCKS_PER_SEC * 1000);
    
	/* Printing binary tree using different traversals */
    printf("\nBinary tree, depth first traversal:\n");
    begin = clock();
    printBinTree_DepthFirstTraversal(head);
    end = clock();
    printf("\nTime of printing tree using  %.3f msec", (double) (end - begin) / CLOCKS_PER_SEC * 1000);
    
    printf("\n\n\rNow the binary tree:\n");
    printBinaryTree(head); //Breath free traversal
    return 0;
}

