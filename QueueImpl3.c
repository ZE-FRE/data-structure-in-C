#include "QueueImpl3.h"
#include <stdio.h>
#include <stdlib.h>

bool InitQueue3(QueueImpl3* queue)
{
	InitStack2(&queue->S1);
	InitStack2(&queue->S2);
	return true;
}

bool Queue3Empty(QueueImpl3* queue)
{
	return Stack2IsEmpty(&queue->S1) && Stack2IsEmpty(&queue->S2);
}

bool EnQueue3(QueueImpl3* queue, int elem)
{
	return PushToStack2(&queue->S1, elem);
}

bool DeQueue3(QueueImpl3* queue, int* elem)
{
	if (Stack2IsEmpty(&queue->S2)) {
		int data;
		while (!Stack2IsEmpty(&queue->S1)) {
			PopFromStack2(&queue->S1, &data);
			PushToStack2(&queue->S2, data);
		}
	}
	if (Stack2IsEmpty(&queue->S2)) // 队列为空
		return false;

	return PopFromStack2(&queue->S2, elem);
}

void DestroyQueue3(QueueImpl3* queue)
{
	DestroyStack2(&queue->S1);
	DestroyStack2(&queue->S2);
}

void testQueueImpl3()
{
	puts("王道第3章代码题，03：利用两个栈S1和S2来模拟一个队列。");
	QueueImpl3 queue;
	InitQueue3(&queue);

	printf("队列是否为空？%d\n", Queue3Empty(&queue));

	EnQueue3(&queue, 1);
	EnQueue3(&queue, 2);
	int elem;
	DeQueue3(&queue, &elem);
	printf("出队：%d\n", elem);

	EnQueue3(&queue, 3);
	EnQueue3(&queue, 4);

	printf("全部出队：");
	while (!Queue3Empty(&queue)) {
		DeQueue3(&queue, &elem);
		printf("%d ", elem);
	}

	DestroyQueue3(&queue);
}
