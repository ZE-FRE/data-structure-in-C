#ifndef QUEUE_H_
#define QUEUE_H_

#include <stdbool.h>

#define QUEUE_INIT_LENGTH 10
#define QUEUE_INCREASE_LENGTH 5

/*
 * 循环队列——用数组实现的队列，空出一个位置出来
 */

typedef int QueueElemType;

typedef struct {
	// 动态数组基址
	QueueElemType* base;
	// 数组长度
	int array_length;
	// 队首
	int front;
	/*
	 * 队尾，指向队列最后一个元素的下一个位置
	 * 队空：front == rear
	 * 队满：rear的后面是front，即(rear+1)%array_length == front
	 */
	int rear;
} Queue;

bool InitQueue(Queue* queue);

void DestroyQueue(Queue* queue);

bool ClearQueue(Queue* queue);

bool QueueEmpty(const Queue* queue);

int QueueLength(const Queue* queue);

bool GetHead(const Queue* queue, QueueElemType *data);

/*
 * 循环队列的动态数组，不好扩容
 * 因此，通常循环队列都需要确定大小，若不能确定大小，则通常采用循环队列
 */
static bool queue_grow(Queue* queue);

bool EnQueue(Queue* queue, const QueueElemType data);

bool DeQueue(Queue* queue, QueueElemType* data);

void QueueTraverse(const Queue* queue);

void testQueue();

#endif
