#ifndef LINK_QUEUE_H_
#define LINK_QUEUE_H_

#include <stdbool.h>

/*
 * 链队列：在实现上，像单链表一样，设一个数据域为空的头结点
 */

typedef int QElemType;

typedef struct QNode {
	QElemType data;
	struct QNode* next;
} QNode;

typedef struct {
	QNode* front;
	QNode* rear;
} LinkQueue;

bool InitLinkQueue(LinkQueue* queue);

void DestroyLinkQueue(LinkQueue* queue);

bool ClearLinkQueue(LinkQueue* queue);

bool LinkQueueEmpty(const LinkQueue* queue);

int LinkQueueLength(const LinkQueue* queue);

bool GetLinkHead(const LinkQueue* queue, QElemType* data);

bool EnLinkQueue(LinkQueue* queue, QElemType data);

bool DeLinkQueue(LinkQueue* queue, QElemType* data);

void LinkQueueTraverse(const LinkQueue* queue);

void testLinkQueue();

#endif
