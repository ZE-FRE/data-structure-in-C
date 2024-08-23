#include "ReusableLinkQueue.h"
#include <stdio.h>
#include <stdlib.h>

bool InitReusableQueue(ReusableLinkQueue* queue)
{
    QLinkNode* newNode = (QLinkNode*)malloc(sizeof(QLinkNode));
    if (!newNode) return false;
    newNode->next = newNode;
    queue->front = queue->rear = newNode;
}

bool ReusableQueueEmpty(ReusableLinkQueue* queue)
{
    return queue->front == queue->rear;
}

bool ReusableQueueFull(ReusableLinkQueue* queue)
{
    return queue->rear->next == queue->front;
}

bool EnReusableQueue(ReusableLinkQueue* queue, QElementType elem)
{
    if (ReusableQueueFull(queue)) {
        QLinkNode* newNode = (QLinkNode*)malloc(sizeof(QLinkNode));
        if (!newNode) return false;
        queue->rear->elem = elem;
        newNode->next = queue->rear->next;
        queue->rear->next = newNode;
        queue->rear = newNode;
    }
    else {
        queue->rear->elem = elem;
        queue->rear = queue->rear->next;
    }
    return true;
}

bool DeReusableQueue(ReusableLinkQueue* queue, QElementType* elem)
{
    if (ReusableQueueEmpty(queue))
        return false;
    *elem = queue->front->elem;
    queue->front = queue->front->next;
    return true;
}

void DestroyReusableQueue(ReusableLinkQueue* queue)
{
    // 从front后一个结点开始释放
    QLinkNode* p = queue->front->next;
    // 用于释放结点
    QLinkNode* q;
    while (p != queue->front) {
        q = p;
        p = p->next;
        free(q);
    }
    // 释放front
    free(queue->front);
    queue->front = queue->rear = NULL;
}

void testReusableLinkQueue()
{
    ReusableLinkQueue queue;
    InitReusableQueue(&queue);
    EnReusableQueue(&queue, newBiNode(1));
    EnReusableQueue(&queue, newBiNode(2));
    EnReusableQueue(&queue, newBiNode(3));
    EnReusableQueue(&queue, newBiNode(4));
    EnReusableQueue(&queue, newBiNode(5));

    QElementType elem;
    while (DeReusableQueue(&queue, &elem))
        printBiNode(elem);

    DestroyReusableQueue(&queue);
}


