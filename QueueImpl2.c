#include "QueueImpl2.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool InitQueue2(QueueImpl2* queue)
{
    queue->base = (QTagNode*)malloc(sizeof(QTagNode) * QUEUE_LENGTH);
    if (!queue->base) return false;
    queue->front = queue->rear = 0;
    for (int i = 0; i < QUEUE_LENGTH; ++i)
        queue->base[i].tag = DE;
    return true;
}

bool Queue2Empty(QueueImpl2* queue)
{
    return queue->front == queue->rear && queue->base[queue->front].tag == DE;
}

bool Queue2Full(QueueImpl2* queue)
{
    return queue->front == queue->rear && queue->base[queue->front].tag == EN;
}

bool EnQueue2(QueueImpl2* queue, QTagElemType elem)
{
    if (Queue2Full(queue)) return false;
    queue->base[queue->rear].elem = elem;
    queue->base[queue->rear].tag = EN;
    queue->rear = (queue->rear + 1) % QUEUE_LENGTH;
    return true;
}

bool DeQueue2(QueueImpl2* queue, QTagElemType* elem)
{
    if (Queue2Empty(queue)) return false;
    *elem = queue->base[queue->front].elem;
    queue->base[queue->front].tag = DE;
    queue->front = (queue->front + 1) % QUEUE_LENGTH;
    return true;
}

void DestroyQueue2(QueueImpl2* queue)
{
    free(queue->base);
    queue->front = queue->rear = 0;
}

// 测试此方法时把队列长度改为1
void testFullAndEmpty()
{
    QueueImpl2 queue;
    InitQueue2(&queue);

    EnQueue2(&queue, "hello");
    EnQueue2(&queue, "world");

    QTagElemType elem;
    if (DeQueue2(&queue, &elem))
        printf("%s\n", elem);

    if (!DeQueue2(&queue, &elem))
        printf("队空");
    DestroyQueue2(&queue);
}

// 测试此方法时把队列长度改大
#pragma warning(disable:4996)
void testCharsInQueue()
{
    QueueImpl2 queue;
    QueueImpl2* q_ptr = &queue;
    InitQueue2(q_ptr);

    char str1[] = "let's study data structure and algorithm using C together";
    char* space = " ";
    char* word = strtok(str1, space);
    while (word) {
        EnQueue2(q_ptr, word);
        word = strtok(NULL, space);
    }

    // 出队4个
    char* elem = NULL;
    for (int i = 0; i < 4; ++i) {
        if (DeQueue2(q_ptr, &elem))
            printf("%s ", elem);
    }

    // 再入队
    char str2[] = "让 我们 一起 学习 数据结构与算法（C语言版） 吧";
    word = strtok(str2, space);
    while (word) {
        EnQueue2(q_ptr, word);
        word = strtok(NULL, space);
    }

    // 全部出队
    while (DeQueue2(q_ptr, &elem))
        printf("%s ", elem);
}


void testQueueImpl2()
{
    //testFullAndEmpty();

    testCharsInQueue();
}
