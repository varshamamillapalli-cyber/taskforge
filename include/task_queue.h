#ifndef TASK_QUEUE_H
#define TASK_QUEUE_H

#include <pthread.h>
#include "task.h"

/* Queue Structure */

typedef struct
{
    Task *front;
    Task *rear;

    int size;

    pthread_mutex_t mutex;

    pthread_cond_t condition;

} TaskQueue;

/* Queue Functions */

void initializeQueue(TaskQueue *queue);

void enqueueTask(TaskQueue *queue, Task *task);

Task *dequeueTask(TaskQueue *queue);

int isQueueEmpty(TaskQueue *queue);

void displayQueue(TaskQueue *queue);

void destroyQueue(TaskQueue *queue);

#endif
