/**
 ******************************************************************************
 *  FILE          : bintree.h
 *  PROJECT       : Binary tree
 *  PROGRAMMER    : Artem Bordiuh
 *  FIRST VERSION : 2017-06-14
 *  DESCRIPTION   : Implementation of binary tree with recursive alphabetical 
					information insert, depth first and breath free traversals
 *****************************************************************************
 **/

#ifndef ASSIGNMENT2ARTEM_BINTREE_H
#define ASSIGNMENT2ARTEM_BINTREE_H

#include <stdint.h>
#include <stdio.h>

// structure defining a binary tree node.  Lower sorted values will go the the left, higher to the right.
typedef struct nodeData {
    char name[30];				// character string of the data being stored in the node
    struct nodeData *left;		// pointer to the next node in the tree that is less than current node OR NULL if empty
    struct nodeData *right;		// pointer to the next node in the tree that is greater than current node OR NULL if empty
} TreeNode;


// data to be stored in tree.  In this case there is just a character string but this could have contained more
typedef struct inputDataStruct{
    char name[30];
} InputData;

/* Functions prototypes */
const TreeNode* createNewNode(const char *name);
void addToBinaryTree_AlphbSort(const TreeNode *data, TreeNode **treeNode);
void printBinTree_DepthFirstTraversal(TreeNode *treeNode);
int height(TreeNode* node);
void printBinaryTree(TreeNode* treeNodeRoot);
void printDepthLevel(TreeNode* root, int level);

#endif //ASSIGNMENT2ARTEM_BINTREE_H
