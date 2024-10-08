﻿#include <stdlib.h>
#include <stdio.h>
#include "../../include/stack/Stack.h"

bool InitStack(Stack* stack)
{
	stack->base = (ElemType*)malloc(sizeof(ElemType) * STACK_INIT_SIZE);
	// 内存分配失败
	if (!stack) return false;
	stack->capacity = STACK_INIT_SIZE;
	stack->top = -1;
	return true;
}

bool IsEmpty(const Stack* stack)
{
	return stack->top == -1;
}
bool IsFull(const Stack* stack)
{
	return Size(stack) == stack->capacity;
}

int Size(const Stack* stack)
{
	return stack->top + 1;
}

bool Push(Stack* stack, const ElemType elem)
{
	// 栈满且扩容失败，返回false
	if (IsFull(stack) && !grow(stack))
		return false;

	stack->base[++stack->top] = elem;
	return true;
}

bool Pop(Stack* stack, ElemType* elem)
{
	if (IsEmpty(stack)) return false;
	*elem = stack->base[stack->top--];
	if (Size(stack) <= SHRINK_THRESHOLD)
		shrink(stack);
	return true;
}

bool Peek(Stack* stack, ElemType* elem)
{
	if (IsEmpty(stack)) return false;
	*elem = stack->base[stack->top];
	return true;
}

void DestroyStack(Stack* stack)
{
	free(stack->base);
}

void shrink(Stack* stack)
{
	//printf("执行了shrink，栈顶元素为：%d\n", stack->base[stack->top]);
	ElemType* ptr = (ElemType*)realloc(stack->base, sizeof(ElemType) * SHRINK_THRESHOLD);
	// 内存分配失败
	if (!ptr) return;
	stack->base = ptr;
	stack->capacity = SHRINK_THRESHOLD;
}

bool grow(Stack* stack)
{
	//printf("执行了扩容，栈顶元素为：%d\n", stack->base[stack->top]);
	int newCapacity = stack->capacity << 1;
	ElemType* ptr = (ElemType*)realloc(stack->base, sizeof(ElemType) * newCapacity);
	// 内存分配失败
	if (!ptr) return false;
	stack->base = ptr;
	stack->capacity = newCapacity;
	return true;
}

void testStackInt()
{
	//Stack stack;
	//InitStack(&stack);
	//Push(&stack, 1);
	//Push(&stack, 2);
	//Push(&stack, 3);
	//Push(&stack, 4);

	//int val = 0;
	//Pop(&stack, &val);
	//printf("%d ", val);
	//Pop(&stack, &val);
	//printf("%d ", val);
	//Pop(&stack, &val);
	//printf("%d ", val);
	//Pop(&stack, &val);
	//printf("%d ", val);
	//DestroyStack(&stack);


	//printf("\n============\n");
	//Stack stack1;
	//InitStack(&stack1);
	//Push(&stack1, 1);
	//Push(&stack1, 2);
	//Pop(&stack1, &val);
	//printf("%d ", val);
	//Push(&stack1, 3);
	//Push(&stack1, 4);
	//Pop(&stack1, &val);
	//printf("%d ", val);
	//Pop(&stack1, &val);
	//printf("%d ", val);
	//Pop(&stack1, &val);
	//printf("%d ", val);
	//// 输出序列应该为：2 4 3 1
	//DestroyStack(&stack1);

}

void testShrinkAndGrow()
{
	//Stack stack;
	//InitStack(&stack);
	//Push(&stack, 1);
	//Push(&stack, 2);
	//Push(&stack, 3);
	//Push(&stack, 4);
	//// 发生扩容，超过阈值，此时capacity == 8
	//Push(&stack, 5);
	//int val = 0;
	//Pop(&stack, &val); // 执行shrink
	//Pop(&stack, &val);
	//Pop(&stack, &val);
	//Pop(&stack, &val);
	//DestroyStack(&stack);
}

void testBiTreeStack()
{
	Stack stack;
	InitStack(&stack);
	Push(&stack, newBiNode(1));
	Push(&stack, newBiNode(2));
	Push(&stack, newBiNode(3));
	Push(&stack, newBiNode(4));
	Push(&stack, newBiNode(5));

	BiNode *node;
	while (Pop(&stack, &node))
		printf("node elem = %d\n", node->elem);

}

void testStack()
{
	//testStackInt();

	//testShrinkAndGrow();

	testBiTreeStack();
}
