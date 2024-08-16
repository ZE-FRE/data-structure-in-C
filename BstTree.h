#ifndef BST_TREE_H_
#define BST_TREE_H_

#include <stdbool.h>

typedef struct BstNode {

	int value;
	struct BstNode* left;
	struct BstNode* right;

	bool visited;

} BstNode, * BstTree;

BstNode* NewNode(int value);

void Init(BstTree* treePtr, int arr[], int length);

void Add(BstTree* treePtr, int value);

void Delete(BstTree* bstTree, int value);

static BstNode* successor(BstNode* bstNode);

/*
 * 非递归先序遍历
 */
void PreOrder(BstTree bstTree, void (*funcptr)(BstNode* node));

void InOrderRecur(BstTree bstTree, void (*funcptr)(BstNode* node));

/*
 * 非递归中序遍历
 */
void InOrder(BstTree bstTree, void (*funcptr)(BstNode* node));
/*
 * 非递归后序遍历
 */
void PostOrder(BstTree bstTree, void (*funcptr)(BstNode* node));

void Destroy(BstTree bstTree);

static void printBstNode(BstNode* node);

void testPreOrder();
void testInOrderRecur();
void testInOrder();
void testPostOrder();

void testBstTree();

#endif
