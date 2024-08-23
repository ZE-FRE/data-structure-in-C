#include "BiTree.h"
#include <stdio.h>
#include <stdlib.h>
#include "Stack.h"
#include "ReusableLinkQueue.h"

void InitBiTree(BiTree* bitree, BiElemType elems[], int len)
{
	Queue queue;
	InitQueue(&queue);
	for (int i = 0; i < len; ++i)
		EnQueue(&queue, elems[i]);
	InitBiTreeFromQueue(bitree, &queue);
	DestroyQueue(&queue);
}

void InitBiTreeFromQueue(BiTree* bitree, Queue* queue)
{
	BiElemType elem;
	if (!DeQueue(queue, &elem) || elem == PLACE_HOLDER) {
		*bitree = NULL;
		return;
	}
	BiNode* newNode = newBiNode(elem);
	if (!newNode) return;
	*bitree = newNode;
	// 生成左子树
	InitBiTreeFromQueue(&(*bitree)->left, queue);
	// 生成右子树
	InitBiTreeFromQueue(&(*bitree)->right, queue);
}

BiNode* newBiNode(BiElemType elem)
{
	BiNode* node = (BiNode*)malloc(sizeof(BiNode));
	// 空间分配失败
	if (!node) return NULL;
	node->elem = elem;
	node->left = node->right = NULL;
	node->visited = false;
	return node;
}

// 后续遍历二叉树，遍历过程中释放结点内存
void DestroyBiTree(BiTree bitree)
{
	if (bitree == NULL) return;
	// 销毁左子树
	DestroyBiTree(bitree->left);
	// 销毁右子树
	DestroyBiTree(bitree->right);
	// 释放二叉树根结点
	free(bitree);
}

void PreOrderRecur(BiTree bstTree, VisitBiNode visit_func)
{
	if (bstTree == NULL) return;
	visit_func(bstTree);
	PreOrderRecur(bstTree->left, visit_func);
	PreOrderRecur(bstTree->right, visit_func);
}

void InOrderRecur(BiTree bstTree, VisitBiNode visit_func)
{
	if (bstTree == NULL) return;
	InOrderRecur(bstTree->left, visit_func);
	visit_func(bstTree);
	InOrderRecur(bstTree->right, visit_func);
}

void PostOrderRecur(BiTree bstTree, VisitBiNode visit_func)
{
	if (bstTree == NULL) return;
	PostOrderRecur(bstTree->left, visit_func);
	PostOrderRecur(bstTree->right, visit_func);
	visit_func(bstTree);
}

void PreOrder(BiTree bitree, VisitBiNode visit_func)
{
	Stack stack;
	Stack* stack_ptr = &stack;
	InitStack(stack_ptr);
	BiNode* node = bitree;
	while (node || !IsEmpty(stack_ptr)) {
		if (node) { // 当前结点存在，则访问后，遍历左子树
			visit_func(node);
			Push(stack_ptr, node);
			node = node->left;
		}
		else { // 从左子树返回
			Pop(stack_ptr, &node);
			node = node->right;
		}
	}
	DestroyStack(stack_ptr);
}

void InOrder(BiTree bitree, VisitBiNode visit_func)
{
	Stack stack;
	Stack* stack_ptr = &stack;
	InitStack(stack_ptr);
	BiNode* node = bitree;
	while (node || !IsEmpty(stack_ptr)) {
		if (node) { // 当前结点存在，遍历左子树
			Push(stack_ptr, node);
			node = node->left;
		}
		else { // 从左子树返回
			Pop(stack_ptr, &node);
			visit_func(node);
			node = node->right;
		}
	}
	DestroyStack(stack_ptr);
}

void PostOrder(BiTree bitree, VisitBiNode visit_func)
{
	Stack stack;
	Stack* stack_ptr = &stack;
	InitStack(stack_ptr);
	BiNode* node = bitree;
	while (node || !IsEmpty(stack_ptr)) {
		if (node) { // 一直往左走
			Push(stack_ptr, node);
			node = node->left;
		}
		else {
			Peek(stack_ptr, &node);
			if (node->right && !node->right->visited) { // 右子树还未访问，表明是从左子树返回的
				// 遍历右子树
				node = node->right;
			}
			else { // 右子树已访问
				Pop(stack_ptr, &node);
				visit_func(node);
				node->visited = true;
				node = NULL;
			}
		}
	}
	DestroyStack(stack_ptr);
}

void LevelOrder(BiTree bitree, VisitBiNode visit_func)
{
	ReusableLinkQueue queue;
	InitReusableQueue(&queue);
	EnReusableQueue(&queue, bitree);
	BiNode* node = NULL;
	while (DeReusableQueue(&queue, &node)) {
		visit_func(node);
		if (node->left)
			EnReusableQueue(&queue, node->left);
		if (node->right)
			EnReusableQueue(&queue, node->right);
	}
}

void printBiNode(BiNode* node)
{
	if (node)
		printf("%d ", node->elem);
}

void testBiTreeTraverse()
{
	/*
	 * 先序：34,24,18,6,14,28,27,32,39,64,42,48,66
	 * 中序：6,14,18,24,27,28,32,34,39,42,48,64,66
	 * 后序：14,6,18,27,32,28,24,48,42,66,64,39,34
	 * 层序：34,24,39,18,28,64,6,27,32,42,66,14,48
	 */

	BiTree bitree = NULL;
	BiElemType elems[] = { 34,24,18,6,'#',14,'#','#','#',28,27,'#','#',32,'#','#',39,'#',64,42,'#',48,'#','#',66,'#','#' };
	InitBiTree(&bitree, elems, sizeof(elems) / sizeof(elems[0]));

	puts("递归遍历二叉树。");

	printf("先序序列：");
	PreOrderRecur(bitree, printBiNode);
	printf("\n中序序列：");
	InOrderRecur(bitree, printBiNode);
	printf("\n后序序列：");
	PostOrderRecur(bitree, printBiNode);

	printf("\n\n非递归遍历二叉树。\n");
	printf("先序序列：");
	PreOrder(bitree, printBiNode);
	printf("\n中序序列：");
	InOrder(bitree, printBiNode);
	printf("\n后序序列：");
	PostOrder(bitree, printBiNode);

	printf("\n\n层序遍历：");
	LevelOrder(bitree, printBiNode);

	DestroyBiTree(bitree);
}

void testBiTree()
{
	testBiTreeTraverse();
}
