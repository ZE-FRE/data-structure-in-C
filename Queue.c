#include "Queue.h"
#include <stdio.h>
#include <stdlib.h>

bool InitQueue(Queue* queue)
{
    QueueElemType* base = (QueueElemType*)malloc(sizeof(QueueElemType) * QUEUE_INIT_LENGTH);
    if (!base) return false;
    queue->base = base;
    queue->array_length = QUEUE_INIT_LENGTH;
    queue->front = queue->rear = 0;
    return true;
}

void DestroyQueue(Queue* queue)
{
    free(queue->base);
}

bool ClearQueue(Queue* queue)
{
    queue->front = queue->front = 0;
    return true;
}

bool QueueEmpty(const Queue* queue)
{
    return queue->front == queue->rear;
}

int QueueLength(const Queue* queue)
{
    return (queue->array_length + queue->rear - queue->front) % queue->array_length;
}

bool GetHead(const Queue* queue, QueueElemType* data)
{
    if (!QueueEmpty(queue)) return false;
    *data = queue->base[queue->front];
    return true;
}

bool queue_grow(Queue* queue)
{
    int newArrLen = queue->array_length + QUEUE_INCREASE_LENGTH;
    if (queue->rear > queue->front) {
        printf("grow1\n");
        QueueElemType* newBase = (QueueElemType*)realloc(queue->base, sizeof(QueueElemType) * newArrLen);
        if (!newBase) return false;
        queue->base = newBase;
        queue->array_length = newArrLen;
    }
    else {
        printf("grow2\n");
        QueueElemType* newBase = (QueueElemType*)malloc(sizeof(QueueElemType) * newArrLen);
        if (!newBase) return false;
        int queue_length = QueueLength(queue);
        QueueElemType data;
        for (int i = 0; i < queue_length; ++i) {
            DeQueue(queue, &data);
            newBase[i] = data;
        }
        free(queue->base);
        queue->base = newBase;
        queue->array_length = newArrLen;
        queue->front = 0;
        queue->rear = queue_length;
        return true;
    }
}

bool EnQueue(Queue* queue, const QueueElemType data)
{
    if ((queue->rear +1 ) % queue->array_length == queue->front)  // 队满，扩容
        if (!queue_grow(queue))
            return false;
    queue->base[queue->rear] = data;
    queue->rear = (queue->rear + 1) % queue->array_length;
    return true;
}

bool DeQueue(Queue* queue, QueueElemType* data)
{
    if (QueueEmpty(queue)) return false;
    *data = queue->base[queue->front];
    queue->front = (queue->front + 1) % queue->array_length;
    return true;
}

void QueueTraverse(const Queue* queue)
{
    int p = queue->front;
    while (p != queue->rear) {
        printf("%d ", queue->base[p]);
        p = (p + 1) % queue->array_length;
    }
}

void testQueue()
{
    Queue queue;
    InitQueue(&queue);
    for (int i = 1; i <= 11; ++i)
        EnQueue(&queue, i);
    printf("队列长度为：%d", QueueLength(&queue));

    printf("\n全部出队：");
    QueueElemType data;
    while (!QueueEmpty(&queue)) 
        if (DeQueue(&queue, &data))
            printf("%d ", data);
    
    printf("\n重新入队：");
    for (int i = 1; i <= 16; ++i)
        EnQueue(&queue, i);
    printf("遍历队列：");
    QueueTraverse(&queue);

    printf("\n全部出队：");
    while (!QueueEmpty(&queue))
        if (DeQueue(&queue, &data))
            printf("%d ", data);
    
    DestroyQueue(&queue);
}
