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

/*==========王道书第3章队列算法题=========*/


/*
02：Q是一个队列，S是一个空栈，实现将队列中的元素逆置的算法。
03：利用两个栈S1和S2来模拟一个队列，已知栈的4个运算定义如下：
Push(S,x);
Pop(S,x);
StackEmpty(S);
StackOverflow(S);
如何利用栈的运算来实现该队列的3个运算？（形参由读者根据要求自己设计）
Enqueue;
Dequeue;
QueueEmpty;
04【2019统考真题】请设计一个队列，要求满足：①初始时队列为空；②入队时，允许增加队列占用空间；③出对后，出队元素所占用的空间可重复利用，即整个队列所占用的空间只增不减；④入队操作和出队操作的时间复杂度始终保持为O(1)。请回答：
1）该队列是应该选择链式存储结构，还是应选择顺序存储结构？
2）画出队列的初始状态，并给出判断队空和队满的条件。
3）画出第一个元素入队后的队列状态。
4）给出入队操作和出队操作的基本过程。
*/

/*==========王道书第3章队列算法题=========*/


#endif
