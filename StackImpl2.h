#ifndef STACK_IMPL_2_H_
#define STACK_IMPL_2_H_

#include <stdbool.h>

#define STACK_INIT_LENGTH 5
#define STACK_INCREASE 2

typedef int StackElemType;

typedef struct {
	// 栈底指针，指向动态数组首地址
	StackElemType* base;
	// 栈顶指针，指向栈顶元素的下一个位置
	StackElemType* top;
	// 动态数组长度
	int length;
} StackImpl2;

bool InitStack2(StackImpl2* stack);

void DestroyStack2(StackImpl2 *stack);

bool Stack2IsEmpty(const StackImpl2* stack);

bool PushToStack2(StackImpl2* stack, const StackElemType data);

bool PopFromStack2(StackImpl2* stack, StackElemType* data);

bool GetTop(const StackImpl2* stack, StackElemType* data);

int Stack2Length(const StackImpl2* stack);

void testStackImpl2();

#endif