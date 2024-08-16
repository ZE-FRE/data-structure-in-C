#ifndef SHARED_STACK_H_
#define SHARED_STACK_H_

#include <stdbool.h>

/*
 * 王道第3章栈代码题，05：设有两个栈S1、S2都采用顺序栈方式，并共享一个存储区[0,...,maxsize-1]，为了尽量利用空间，
 * 减少溢出的可能，可采用栈顶相向、迎面增长的存储方式。试设计S1、S2有关入栈和出栈的操作算法。
 * date:2024/8/16
 */
#define SHARED_STACK_ARRAY_LENGTH 5
typedef int SharedStackElemType;

typedef struct {
	// S1的栈底和栈顶指针，栈顶指针指向栈顶元素的下一个位置，当top1==top2时，栈满，因此会浪费一个存储空间
	SharedStackElemType* base1, *top1;
	// S2的栈底和栈顶指针
	SharedStackElemType* base2, *top2;
} SharedStack;

bool InitSharedStack(SharedStack* sharedStack);

bool Stack1Empty(SharedStack* sharedStack);
bool Stack2Empty(SharedStack* sharedStack);

bool SharedStackFull(SharedStack* sharedStack);

bool Stack1Push(SharedStack* sharedStack, SharedStackElemType elem);
bool Stack1Pop(SharedStack* sharedStack, SharedStackElemType* elem);

bool Stack2Push(SharedStack* sharedStack, SharedStackElemType elem);
bool Stack2Pop(SharedStack* sharedStack, SharedStackElemType* elem);

void DestroySharedStack(SharedStack* sharedStack);

void testSharedStack();

#endif
