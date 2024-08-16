#ifndef QUEUE_IMPL2_H_
#define QUEUE_IMPL2_H_

#include <stdbool.h>

/*==========王道书第3章队列算法题=========*/

/*
 * 01：若希望循环队列中的元素都能得到利用，则需设置一个标志域tag，
 * 并以tag的值为0或1来区分头指针front和队尾指针rear相同时的队列状态是“空”还是“满”。试编写与此结构相应的入队和出队算法。
 * date:2024/8/16
 */
#define QUEUE_LENGTH 1
typedef char* QTagElemType;
typedef enum {
	EN = 1,
	DE = 0
} QTag;
typedef struct {
	QTagElemType elem;
	// 默认初始化为EN
	QTag tag;
} QTagNode;

typedef struct {
	QTagNode* base;
	int front;
	// 指向队列最后一个元素的下一个位置
	int rear;
} QueueImpl2;

bool InitQueue2(QueueImpl2* queue);

bool Queue2Empty(QueueImpl2* queue);

bool Queue2Full(QueueImpl2* queue);

bool EnQueue2(QueueImpl2* queue, QTagElemType elem);

bool DeQueue2(QueueImpl2* queue, QTagElemType* elem);

void DestroyQueue2(QueueImpl2* queue);

void testQueueImpl2();

#endif
