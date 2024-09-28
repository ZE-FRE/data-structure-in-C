#include <stdio.h>
#include <stdlib.h>
#include "../../include/queue/LinkQueue.h"

bool InitLinkQueue(LinkQueue* queue)
{
	// 创建头结点
	QNode* head = (QNode*)malloc(sizeof(QNode));
	if (!head) return false;
	head->next = NULL;
	queue->front = queue->rear = head;
	return true;
}

void DestroyLinkQueue(LinkQueue* queue)
{
	ClearLinkQueue(queue);
	free(queue->front);
	queue->front = queue->rear = NULL;
}

bool ClearLinkQueue(LinkQueue* queue)
{
	QNode* p = queue->front->next;
	QNode* q;
	while (p) {
		q = p;
		p = p->next;
		free(q);
	}
	queue->front->next = NULL;
	queue->rear = queue->front;
	return true;
}

bool LinkQueueEmpty(const LinkQueue* queue)
{
	return queue->front == queue->rear;
}

int LinkQueueLength(const LinkQueue* queue)
{
	int length = 0;
	for (QNode* p = queue->front->next; p; p = p->next)
		++length;
	return length;
}

bool GetLinkHead(const LinkQueue* queue, QElemType* data)
{
	if (LinkQueueEmpty(queue)) return false;
	*data = queue->front->next->data;
	return true;
}

bool EnLinkQueue(LinkQueue* queue, QElemType data)
{
	QNode* newNode = (QNode*)malloc(sizeof(QNode));
	if (!newNode) return false;
	newNode->data = data;
	newNode->next = NULL;
	queue->rear->next = newNode;
	queue->rear = newNode;
	return true;
}

bool DeLinkQueue(LinkQueue* queue, QElemType* data)
{
	if (LinkQueueEmpty(queue)) return false;
	QNode* oldFirst = queue->front->next;
	*data = oldFirst->data;
	queue->front->next = oldFirst->next;
	if (oldFirst == queue->rear) queue->rear = queue->front;
	free(oldFirst);
	return true;
}

void LinkQueueTraverse(const LinkQueue* queue)
{
	for (QNode* p = queue->front->next; p; p = p->next) 
		printf("%d ", p->data);
}

void testLinkQueue()
{
	LinkQueue queue;
	InitLinkQueue(&queue);
	for (int i = 1; i <= 10; ++i) 
		EnLinkQueue(&queue, i);

	printf("出队5个：");
	QElemType data;
	for (int i = 1; i <= 5; ++i)
		if (DeLinkQueue(&queue, &data))
			printf("%d ", data);
	printf("\n遍历队列剩余元素：");
	LinkQueueTraverse(&queue);
	DestroyLinkQueue(&queue);
}
