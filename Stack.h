#ifndef STACK_H_
#define STACK_H_

#include <stdbool.h>
#include "BstTree.h"

// 动态数组收缩阈值
#define SHRINK_THRESHOLD 4

typedef BstNode* ElemType;

typedef struct 
{
	// 动态数组基址
	ElemType* base;
	// 动态数组大小
	int capacity;
	// 栈顶，-1表示栈为空。另一种方案是指向栈顶的下一个位置，这样就初始化为0
	int top;
} Stack;

bool InitStack(Stack* stack, int initSize);

bool IsEmpty(const Stack* stack);

bool IsFull(const Stack* stack);

int Size(const Stack* stack);

bool Push(Stack* stack, const ElemType elem);

bool Pop(Stack* stack, ElemType* elem);

bool Peek(Stack* stack, ElemType* elem);

void DestroyStack(Stack* stack);

static void shrink(Stack* stack);

static bool grow(Stack* stack);


void testStackInt();
/*
 * 需要暂时把SHRINK_THRESHOLD改为4
 */
void testShrinkAndGrow();

void testBstTreeStack();
void testStack();

#endif
