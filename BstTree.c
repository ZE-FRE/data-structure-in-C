#include <stdio.h>
#include <stdlib.h>
#include "BstTree.h"

#include "Stack.h"

void InitBstTree(BstTree* treePtr, BstElemType arr[], int length)
{
	*treePtr = NULL;
	for (int i = 0; i < length; ++i)
		BstInsertRecur(treePtr, arr[i]);
}

void BstInsertRecur(BstTree* treePtr, BstElemType elem)
{
	BstNode* node = *treePtr;
	// 找到结点的插入位置
	if (*treePtr == NULL)
		*treePtr = newBiNode(elem);
	else if (elem < node->elem)
		BstInsertRecur(&node->left, elem);
	else if (elem > node->elem)
		BstInsertRecur(&node->right, elem);
	else // 结点值重复
		return;
}

void BstInsert(BstTree* treePtr, BstElemType elem) 
{
	if (*treePtr == NULL) { // 空树插入第一个结点
		*treePtr = newBiNode(elem);
		return;
	}
	
	BstNode* parent = NULL, *node = *treePtr;
	// 找插入位置
	while (node) {
		if (elem < node->elem) {
			parent = node;
			node = node->left;
		}
		else if (elem > node->elem) {
			parent = node;
			node = node->right;
		}
		else // 结点值已存在
			return;
	}
	// 插入结点
	node = newBiNode(elem);
	if (elem < parent->elem)
		parent->left = node;
	else
		parent->right = node;
}

void BstDelete(BstTree* bstTree, BstElemType elem)
{
	// 空树
	if (*bstTree == NULL) return;

	// 查找删除结点
	BstNode* deletedNode = *bstTree;
	BstNode* parent = NULL;
	while (deletedNode) {
		if (elem < deletedNode->elem) {
			parent = deletedNode;
			deletedNode = deletedNode->left;
		}
		else if (elem > deletedNode->elem) {
			parent = deletedNode;
			deletedNode = deletedNode->right;
		}
		else // 找到删除结点
			break;
	}
	// 结点不存在
	if (!deletedNode) return;

	if (deletedNode->left && deletedNode->right) { // 左右子树都存在，找后继来代替
		BstNode* successor = deletedNode->right;
		parent = deletedNode;
		while (successor->left) {
			parent = successor;
			successor = successor->left;
		}
		deletedNode->elem = successor->elem;
		deletedNode = successor;
	}
	BstNode* alternate = deletedNode->left ? deletedNode->left : deletedNode->right;
	if (parent == NULL) { // 删除的是根结点
		*bstTree = alternate;
	}
	else {
		if (parent->left == deletedNode)
			parent->left = alternate;
		else
			parent->right = alternate;
	}
	free(deletedNode);
}

void testBstDelete()
{
	BstElemType elems[] = { 34, 24, 18, 39, 28, 6, 64, 14, 42, 48, 32, 66, 27 };
	BstTree bstTree = NULL;
	InitBstTree(&bstTree, elems, sizeof(elems) / sizeof(elems[0]));
	printf("原始二叉排序树：");
	InOrder(bstTree, printBiNode);
	printf("\n删除有左右孩子的分支结点24：");
	BstDelete(&bstTree, 24);
	InOrder(bstTree, printBiNode);
	DestroyBiTree(bstTree);

	InitBstTree(&bstTree, elems, sizeof(elems) / sizeof(elems[0]));
	printf("\n删除只有左孩子的分支结点18：");
	BstDelete(&bstTree, 18);
	InOrder(bstTree, printBiNode);
	DestroyBiTree(bstTree);

	InitBstTree(&bstTree, elems, sizeof(elems) / sizeof(elems[0]));
	printf("\n删除只有右孩子的分支结点42：");
	BstDelete(&bstTree, 42);
	InOrder(bstTree, printBiNode);
	DestroyBiTree(bstTree);

	InitBstTree(&bstTree, elems, sizeof(elems) / sizeof(elems[0]));
	printf("\n删除叶子结点48：");
	BstDelete(&bstTree, 48);
	InOrder(bstTree, printBiNode);
	DestroyBiTree(bstTree);

	InitBstTree(&bstTree, elems, sizeof(elems) / sizeof(elems[0]));
	printf("\n删除根结点34：");
	BstDelete(&bstTree, 34);
	InOrder(bstTree, printBiNode);
	DestroyBiTree(bstTree);

}


void testBstTree()
{
	testBstDelete();
}

