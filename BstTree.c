#include <stdio.h>
#include <stdlib.h>
#include "BstTree.h"

#include "Stack.h"

BstNode* NewNode(int value)
{
	BstNode* node = (BstNode*)malloc(sizeof(BstNode));
	// 空间分配失败
	if (!node) return NULL;
	node->value = value;
	node->left = NULL;
	node->right = NULL;
	node->visited = false;
	return node;
}

void Init(BstTree* treePtr, int arr[], int length)
{
	*treePtr = NULL;
	for (int i = 0; i < length; ++i)
		Add(treePtr, arr[i]);
}

void Add(BstTree* treePtr, int value)
{
	BstNode* node = *treePtr;
	// 找到结点的插入位置
	if (*treePtr == NULL)
		*treePtr = NewNode(value);
	else if (value < node->value)
		Add(&node->left, value);
	else if (value > node->value)
		Add(&node->right, value);
	else // 结点值重复
		return;
}

void Delete(BstTree* bstTree, int value)
{
	// 空树
	if (*bstTree == NULL) return;

	// 查找删除结点
	BstNode* deletedNode = *bstTree;
	BstNode* parent = NULL;
	while (!deletedNode) {
		if (value < deletedNode->value)
			deletedNode = deletedNode->left;
		else if (value > deletedNode->value)
			deletedNode = deletedNode->right;
		else // 找到删除结点
			break;
		parent = deletedNode;
	}
	// 结点不存在
	if (!deletedNode) return;

	if (deletedNode->left && deletedNode->right) { // 左右子树都存在，找后继来代替
		BstNode* succe= successor(deletedNode);
		deletedNode->value = succe->value;
		Delete(succe, succe->value);
		return;
	}
	BstNode* alternate = deletedNode->left ? deletedNode->left : deletedNode->right;
	if (parent == NULL) // 

	if (parent->left == deletedNode)
		parent->left = alternate;
	else
		parent->right = alternate;
	free(deletedNode);
}

BstNode* successor(BstNode* bstNode)
{
	if (!bstNode) return NULL;
	BstNode* successor = bstNode->right;
	while (successor->left)
		successor = successor->left;
	return successor;
}

void PreOrder(BstTree bstTree, void(*funcptr)(BstNode* node))
{
	if (!bstTree || !funcptr) return;
	Stack stack;
	InitStack(&stack, 10);
	BstNode* node = bstTree;
	while (node || !IsEmpty(&stack)) {
		if (node) {
			// 访问结点
			funcptr(node);
			Push(&stack, node);
			node = node->left;
		}
		else {
			Pop(&stack, &node);
			node = node->right;
		}
	}
	DestroyStack(&stack);
}

void InOrderRecur(BstTree bstTree, void (*funcptr)(BstNode* node))
{
	if (!bstTree) return;
	InOrderRecur(bstTree->left, funcptr);
	funcptr(bstTree);
	InOrderRecur(bstTree->right, funcptr);
}

void InOrder(BstTree bstTree, void (*funcptr)(BstNode* node))
{
	//if (!bstTree || !funcptr) return;
	//Stack stack;
	//InitStack(&stack, 10);

	//// 当前遍历结点
	//BstNode* node = bstTree;
	//Push(&stack, node);
	//while (node || !IsEmpty(&stack)) {
	//	if (node) {
	//		node = node->left;
	//		if (node) Push(&stack, node);
	//	} else {
	//		// 左子树遍历完毕，访问当前结点
	//		Pop(&stack, &node);
	//		funcptr(node);
	//		// 遍历右子树
	//		node = node->right;
	//		if (node) Push(&stack, node);
	//	}
	//}
	//DestroyStack(&stack);
	if (!bstTree || !funcptr) return;
	Stack stack;
	InitStack(&stack, 10);
	// 当前遍历结点
	BstNode* node = bstTree;
	while (node || !IsEmpty(&stack)) {
		if (node) {
			// 当前结点不为空
			Push(&stack, node);
			// 遍历左子树
			node = node->left;
		}
		else {
			// 左子树遍历完毕，访问当前结点
			Pop(&stack, &node);
			funcptr(node);
			// 遍历右子树
			node = node->right;
		}
	}
	DestroyStack(&stack);
}

void PostOrder(BstTree bstTree, void (*funcptr)(BstNode* node))
{
	if (!bstTree || !funcptr) return;
	Stack stack;
	InitStack(&stack, 10);
	// 当前遍历结点
	BstNode* node = bstTree;
	while (node || !IsEmpty(&stack)) {
		if (node) {
			// 当前结点不为空
			Push(&stack, node);
			// 遍历左子树
			node = node->left;
		}
		else { // 子树遍历完成，需要区分是从左子树返回还是右子树返回
			Peek(&stack, &node);
			if (node->right && !node->right->visited) { // 左子树遍历完毕
				// 遍历右子树
				node = node->right;
			}
			else { // 右子树遍历完毕，访问当前结点
				// 结点退栈，访问结点
				Pop(&stack, &node);
				funcptr(node);
				node->visited = true;
				node = NULL;
			}
		}
			
	}
	DestroyStack(&stack);
}

void Destroy(BstTree bstTree)
{
	if (!bstTree) return;
	Destroy(bstTree->left);
	Destroy(bstTree->right);
	free(bstTree);
}

void printBstNode(BstNode* node)
{
	if (node) printf("%d ", node->value);
}

void testPreOrder()
{
	printf("\n先序非递归遍历二叉搜索树 ");
	int arr[] = { 34, 24, 18, 39, 28, 6, 64, 14, 42, 48, 32, 66, 27 };
	// 先序：34,  24, 18, 6, 14, 28, 27, 32, 39, 64, 42, 48, 66
	BstTree bstTree = NULL;
	Init(&bstTree, arr, 13);
	PreOrder(bstTree, printBstNode);
	Destroy(bstTree);
}

void testInOrderRecur()
{
	/*
	* 初始化一颗二叉排序树
	*            34
	*          /    \
	*        24      39
	*      /   \       \
	*    18    28      64
	*   /     /  \    /  \
	*  6     27  32  42  66
	*   \              \
	*   14             48
	*/
	printf("\n中序递归遍历二叉搜索树 ");
	int arr[] = { 34, 24, 18, 39, 28, 6, 64, 14, 42, 48, 32, 66, 27 };
	// 中序：6, 14, 18, 24, 27, 28, 32, 34, 39, 42, 48, 64, 66
	BstTree bstTree = NULL;
	Init(&bstTree, arr, 13);
	InOrderRecur(bstTree, printBstNode);
	Destroy(bstTree);
	bstTree = NULL;
}

void testInOrder()
{
	printf("\n中序非递归遍历二叉搜索树 ");
	int arr[] = { 34, 24, 18, 39, 28, 6, 64, 14, 42, 48, 32, 66, 27 };
	// 中序：6, 14, 18, 24, 27, 28, 32, 34, 39, 42, 48, 64, 66
	BstTree bstTree = NULL;
	Init(&bstTree, arr, 13);
	InOrder(bstTree, printBstNode);
	Destroy(bstTree);
}

void testPostOrder()
{
	printf("\n后序非递归遍历二叉搜索树 ");
	int arr[] = { 34, 24, 18, 39, 28, 6, 64, 14, 42, 48, 32, 66, 27 };
	// 后序：14, 6, 18, 27, 32, 28, 24, 48, 42, 66, 64, 39, 34
	BstTree bstTree = NULL;
	Init(&bstTree, arr, 13);
	PostOrder(bstTree, printBstNode);
	Destroy(bstTree);
}



void testBstTree()
{
	testPreOrder();

	testInOrderRecur();
	
	testInOrder();

	testPostOrder();
}

