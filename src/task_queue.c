#include <stdio.h>
#include <stdlib.h>

#include "../include/task_queue.h"

/* Initialize Queue */

void initializeQueue(TaskQueue *queue)
{
    queue->front = NULL;
    queue->rear = NULL;
    queue->size = 0;

    pthread_mutex_init(&queue->mutex, NULL);
    pthread_cond_init(&queue->condition, NULL);
}

/* Check Empty */

int isQueueEmpty(TaskQueue *queue)
{
    return (queue->front == NULL);
}

/* Insert Task */

void enqueueTask(TaskQueue *queue, Task *task)
{
    pthread_mutex_lock(&queue->mutex);

    task->next = NULL;

    if(queue->rear == NULL)
    {
        queue->front = task;
        queue->rear = task;
    }
    else
    {
        queue->rear->next = task;
        queue->rear = task;
    }

    queue->size++;

    printf("\n[QUEUE] Task %d added successfully.\n", task->taskID);

    pthread_cond_signal(&queue->condition);

    pthread_mutex_unlock(&queue->mutex);
}

/* Remove Task */

Task *dequeueTask(TaskQueue *queue)
{
    pthread_mutex_lock(&queue->mutex);

    while(queue->front == NULL)
    {
        pthread_cond_wait(&queue->condition, &queue->mutex);
    }

    Task *task = queue->front;

    queue->front = queue->front->next;

    if(queue->front == NULL)
    {
        queue->rear = NULL;
    }

    queue->size--;

    pthread_mutex_unlock(&queue->mutex);

    return task;
}

/* Display Queue */

void displayQueue(TaskQueue *queue)
{
    pthread_mutex_lock(&queue->mutex);

    printf("\n================ TASK QUEUE ================\n");

    if(queue->front == NULL)
    {
        printf("Queue is Empty.\n");
    }
    else
    {
        Task *current = queue->front;

        printf("ID\tTask Name\t\tStatus\n");
        printf("--------------------------------------------\n");

        while(current != NULL)
        {
            printf("%d\t%-20s\t%d\n",
                   current->taskID,
                   current->taskName,
                   current->status);

            current = current->next;
        }
    }

    printf("============================================\n");

    pthread_mutex_unlock(&queue->mutex);
}

/* Destroy Queue */

void destroyQueue(TaskQueue *queue)
{
    pthread_mutex_destroy(&queue->mutex);
    pthread_cond_destroy(&queue->condition);
}
