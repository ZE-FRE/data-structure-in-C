#include "stdio.h"
#include "stdlib.h"
#include "../../include/stack/SharedStack.h"

bool InitSharedStack(SharedStack* sharedStack)
{
	sharedStack->base1 = sharedStack->top1 = (SharedStackElemType*)malloc(sizeof(SharedStackElemType) * SHARED_STACK_ARRAY_LENGTH);
	if (sharedStack->base1 == NULL) return false;
	sharedStack->base2 = sharedStack->top2 = sharedStack->base1 + SHARED_STACK_ARRAY_LENGTH - 1;
	return true;
}

bool Stack1Empty(SharedStack* sharedStack)
{
	return sharedStack->base1 == sharedStack->top1;
}

bool Stack2Empty(SharedStack* sharedStack)
{
	return sharedStack->base2 == sharedStack->top2;
}

bool SharedStackFull(SharedStack* sharedStack)
{
	return sharedStack->top1 == sharedStack->top2;
}

bool Stack1Push(SharedStack* sharedStack, SharedStackElemType elem)
{
	if (SharedStackFull(sharedStack)) return false;
	*sharedStack->top1++ = elem;
	return true;
}

bool Stack1Pop(SharedStack* sharedStack, SharedStackElemType* elem)
{
	if (Stack1Empty(sharedStack)) return false;
	*elem = *--sharedStack->top1;
	return true;
}

bool Stack2Push(SharedStack* sharedStack, SharedStackElemType elem)
{
	if (SharedStackFull(sharedStack)) return false;
	*sharedStack->top2-- = elem;
	return true;
}

bool Stack2Pop(SharedStack* sharedStack, SharedStackElemType* elem)
{
	if (Stack2Empty(sharedStack)) return false;
	*elem = *++sharedStack->top2;
	return true;
}

void DestroySharedStack(SharedStack* sharedStack)
{
	free(sharedStack->base1);
}

void testSharedStack()
{
	SharedStack sharedStack;
	InitSharedStack(&sharedStack);
	Stack1Push(&sharedStack, 1);
	Stack2Push(&sharedStack, 1);
	Stack1Push(&sharedStack, 2);
	Stack2Push(&sharedStack, 2);
	Stack1Push(&sharedStack, 3);
	Stack2Push(&sharedStack, 3);

	int elem;
	printf("栈S1出栈序列：");
	while (!Stack1Empty(&sharedStack)) {
		Stack1Pop(&sharedStack, &elem);
		printf("%d ", elem);
	}
	printf("\n栈S2出栈序列：");
	while (!Stack2Empty(&sharedStack)) {
		Stack2Pop(&sharedStack, &elem);
		printf("%d ", elem);
	}
	DestroySharedStack(&sharedStack);
}
