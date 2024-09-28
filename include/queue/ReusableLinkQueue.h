#ifndef REUSABLE_LINK_QUEUE_H_
#define REUSABLE_LINK_QUEUE_H_

#include <stdbool.h>
#include "../../include/bitree/BiTree.h"

/*==========王道书第3章队列算法题=========*/

/*
 * 04【2019统考真题】请设计一个队列，要求满足：
 * ①初始时队列为空；
 * ②入队时，允许增加队列占用空间；
 * ③出队后，出队元素所占用的空间可重复利用，即整个队列所占用的空间只增不减；
 * ④入队操作和出队操作的时间复杂度始终保持为O(1)。
 * 请回答：
 * 1）该队列是应该选择链式存储结构，还是应选择顺序存储结构？
 * 2）画出队列的初始状态，并给出判断队空和队满的条件。
 * 3）画出第一个元素入队后的队列状态。
 * 4）给出入队操作和出队操作的基本过程。
 */

/*
 * 解答：
 * date:2024/8/20
 * 1）应选择链式存储结构。因为题目要求入队的时间复杂度必须恒O(1)，若采用顺序存储，则当入队引发扩容时，时间复杂度就不是恒为O(1)。
 * 2）可采用循环链表来实现，在实现时，参考数组实现的循环队列，也空出一个结点来不用，方便区分队空还是队满，
 *	  初始时front和rear都指向空闲结点（不存放有效数据的结点）
 *	   front  rear
 *		 ↓	   ↓
 *	  +-------+-----+
 *	  |空闲结点| next|--- 
 *	  +-------+-----+  |
 *		 ↑			   |
 *		 |-------------|
 *	  队空条件：front == rear
 *	  队满条件：rear->next == front
 *	  初始时，队既是空的，又是满的
 * 3）第一个元素入队后，队列中只有一个结点，front和rear均指向此结点，rear->next == front
 *		front			  rear
 *		 ↓					↓
 *	  +-----+-----+		+-----+-----+
 *	  |elem | next|---> |     | next|
 *	  +-----+-----+     +-----+-----+
 *		 ↑						  |
 *		 |------------------------|
 *		 
 */

typedef BiNode* QElementType;

typedef struct QLinkNode {
	QElementType elem;
	struct QLinkNode* next;
} QLinkNode;

typedef struct {
	QLinkNode* front;
	// 指向队列最后一个结点的下一个位置
	QLinkNode* rear;
} ReusableLinkQueue;

bool InitReusableQueue(ReusableLinkQueue* queue);

bool ReusableQueueEmpty(ReusableLinkQueue* queue);

bool ReusableQueueFull(ReusableLinkQueue* queue);

/*
 * 入队操作，若队满就动态分配空间
 */
bool EnReusableQueue(ReusableLinkQueue* queue, QElementType elem);

/*
 * 出队操作
 */
bool DeReusableQueue(ReusableLinkQueue* queue, QElementType *elem);

void DestroyReusableQueue(ReusableLinkQueue* queue);

void testReusableLinkQueue();

#endif
