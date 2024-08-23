#ifndef QUEUE_BASED_ON_STACK_
#define QUEUE_BASED_ON_STACK_

#include <stdbool.h>

/*==========王道书第3章队列算法题=========*/

/*
 * 03：利用两个栈S1和S2来模拟一个队列，已知栈的4个运算定义如下：
 * Push(S,x);
 * Pop(S,x);
 * StackEmpty(S);
 * StackOverflow(S);
 * 如何利用栈的运算来实现该队列的3个运算？（形参由读者根据要求自己设计）
 * Enqueue;
 * Dequeue;
 * QueueEmpty;
 * 
 * date:2024/8/19
 * 思路：栈S1用于入队，S2用于出队。
 * 队空条件：S1和S2都为空栈
 * 入队：向S1入栈
 * 出队：S2栈顶元素出栈，若S2为空，则将S1的元素全部依次出栈，再全部向S2入栈，然后2栈顶元素再出栈
 */

#include "StackImpl2.h"
typedef struct {
	StackImpl2 S1;
	StackImpl2 S2;
} QueueImpl3;

bool InitQueue3(QueueImpl3* queue);

bool Queue3Empty(QueueImpl3* queue);

bool EnQueue3(QueueImpl3* queue, int elem);

bool DeQueue3(QueueImpl3* queue, int *elem);

void DestroyQueue3(QueueImpl3* queue);

void testQueueImpl3();

#endif
