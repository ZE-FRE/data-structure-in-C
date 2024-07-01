#include <stdio.h>
#include <stdlib.h>
#include "BstTree.h"

BstNode* NewNode(int value)
{
	BstNode* node = (BstNode*)malloc(sizeof(BstNode));
	// �ռ����ʧ��
	if (!node) return NULL;
	node->value = value;
	node->left = NULL;
	node->right = NULL;
	return node;
}

void Init(BstTree* treePtr, int arr[], int length)
{
	for (int i = 0; i < length; ++i)
		Add(treePtr, arr[i]);
}

void Add(BstTree* treePtr, int value)
{
	BstNode* node = *treePtr;
	// �ҵ����Ĳ���λ��
	if (*treePtr == NULL)
		*treePtr = NewNode(value);
	else if (value < node->value)
		Add(&node->left, value);
	else if (value > node->value)
		Add(&node->right, value);
	else // ���ֵ�ظ�
		return;
}

void InOrder(BstTree bstTree, void(*funcptr)(BstNode* node))
{
	if (!bstTree) return;
	InOrder(bstTree->left, funcptr);
	funcptr(bstTree);
	InOrder(bstTree->right, funcptr);
}

void Destroy(BstTree bstTree)
{
	if (!bstTree) return;
	Destroy(bstTree->left);
	Destroy(bstTree->right);
	free(bstTree);
}

void print(BstNode* node)
{
	if (node) printf("%d ", node->value);
}


void testBstTree()
{
	int arr[] = { 34, 24, 18, 39, 28, 6, 64, 14, 42, 48, 32, 66, 27 };
	// ����6, 14, 18, 24, 27, 28, 32, 34, 39, 42, 48, 64, 66
	BstTree bstTree = NULL;
	Init(&bstTree, arr, 13);
	InOrder(bstTree, print);
	Destroy(bstTree);
	bstTree = NULL;
}


