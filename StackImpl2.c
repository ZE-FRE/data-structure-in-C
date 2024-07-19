#include "StackImpl2.h"
#include <stdio.h>
#include <stdlib.h>

bool InitStack2(StackImpl2* stack)
{
    StackElemType* base = (StackElemType*)malloc(sizeof(StackElemType) * STACK_INIT_LENGTH);
    if (!base) return false;
    stack->base = stack->top = base;
    stack->length = STACK_INIT_LENGTH;
    return true;
}

void DestroyStack2(StackImpl2* stack)
{
    if (stack)
        free(stack->base);
}

bool Stack2IsEmpty(const StackImpl2* stack)
{
    return !stack || stack->base == stack->top;
}

bool PushToStack2(StackImpl2* stack, const StackElemType data)
{
    if (stack->top - stack->base >= stack->length) { // 栈满，扩容
        printf("扩容了\n");
        int oldLength = stack->length;
        int newLength = oldLength + STACK_INCREASE;
        StackElemType* newBase = (StackElemType*)realloc(stack->base, sizeof(StackElemType) * newLength);
        if (!newBase) return false;
        stack->base = newBase;
        stack->top = stack->base + oldLength;
        stack->length = newLength;
    }
    *stack->top++ = data;
    return true;
}

bool PopFromStack2(StackImpl2* stack, StackElemType* data)
{
    if (Stack2IsEmpty(stack)) return false;
    *data = *--stack->top;
    return true;
}

bool GetTop(const StackImpl2* stack, StackElemType* data)
{
    if (Stack2IsEmpty(stack)) return false;
    *data = *(stack->top - 1);
    return true;
}

int Stack2Length(const StackImpl2* stack)
{
    return stack->length;
}

void testStackImpl2()
{
    StackImpl2 stack;
    InitStack2(&stack);
    for (int i = 1; i <= STACK_INIT_LENGTH + 3; ++i)
        PushToStack2(&stack, i);
    StackElemType data;
    if (GetTop(&stack, &data))
        printf("top data is %d ", data);
    printf("\nstack data is: ");
    for (int i = 0; i < Stack2Length(&stack); ++i) 
        if (PopFromStack2(&stack, &data))
            printf("%d ", data);
    if (!PopFromStack2(&stack, &data))
        printf("\nstack is empty");
    DestroyStack2(&stack);
}
