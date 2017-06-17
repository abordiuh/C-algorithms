/**
 ******************************************************************************
 *  FILE          : bintree.c
 *  PROJECT       : Binary tree
 *  PROGRAMMER    : Artem Bordiuh
 *  FIRST VERSION : 2017-06-14
 *  DESCRIPTION   : Implementation of binary tree with recursive alphabetical 
					information insert, depth first and breath free traversals
 *****************************************************************************
 **/
 
#include "bintree.h"

/**
 * @brief  Creating the new binary tree node.
 * @param  String name data
 * @retval Binary tree node pointer
 */
const TreeNode* createNewNode(const char *name){
    if(name != NULL || strlen(name) >= 30) {
        TreeNode *newNode = malloc(sizeof(TreeNode));
        sprintf(newNode->name, "%s", name);
        newNode->left = NULL;
        newNode->right = NULL;
        return newNode;
    } else return NULL;
}

/**
 * @brief  Adding to binary tree data in alphabetical order
 * @param  Pointer to a new node to add to tree
 * @param  Binary tree header pointer
 * @retval None
 */
void addToBinaryTree_AlphbSort(const TreeNode *data, TreeNode **treeNode){
    if(data != NULL ){
        if( *treeNode == NULL ){
            *treeNode = (TreeNode*)data;
        } else
        if(strcmp((*treeNode)->name, data->name)>=0){
            addToBinaryTree_AlphbSort( data, &(*treeNode)->left );
        }
        else {
            addToBinaryTree_AlphbSort( data, &(*treeNode)->right );
        }
    } else printf("Can't add to binary tree, data is empty or too long");
}

/**
 * @brief  Printing binary tree with depth first traversal
 * @param  Binary tree header pointer
 * @retval None
 */
void printBinTree_DepthFirstTraversal(TreeNode *treeNode){
    // add code to print data in order
    if(treeNode->left != NULL){
        printBinTree_DepthFirstTraversal(treeNode->left);
    }

    printf("%s ", treeNode->name);

    if(treeNode->right != NULL) {
        printBinTree_DepthFirstTraversal(treeNode->right);
    }
}
/*
 * @brief  Function to print breath free, level order traversal of a tree
 * @param  Binary tree header pointer
 * @retval None
 */
void printBinaryTree(TreeNode* treeNodeRoot)
{
    int h = height(treeNodeRoot);
    for (int i=1; i<=h; i++){
        printDepthLevel(treeNodeRoot, i);
        printf("\n");
    }
}

/*
 * @brief  Print nodes at a given level
 * @param  Binary tree root pointer
 * @param  Binary tree current depth level 
 * @retval None
 */
void printDepthLevel(TreeNode* root, int level)
{
    if (root == NULL){
        printf("\t");
        return;
    }
    if (level == 1){
        printf("%s \t", root->name);
    }
    else if (level > 1)
    {
        printDepthLevel(root->left, level-1);
        printDepthLevel(root->right, level-1);
    }
}

/*
 * @brief  Calculating height of the binary tree
 * @param  Binary tree header pointer
 * @retval Height of a binary tree
 */
int height(TreeNode* node)
{
    if (node==NULL)
        return 0;
    else
    {
        /* Calculate the height of each subtree */
        int lheight = height(node->left);
        int rheight = height(node->right);
		
        if (lheight > rheight)
            return(lheight+1);
        else return(rheight+1);
    }
}

