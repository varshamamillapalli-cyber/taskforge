#ifndef THREAD_POOL_H
#define THREAD_POOL_H

#include <pthread.h>
#include "task_queue.h"

typedef struct
{
    pthread_t workers[MAX_THREADS];

    TaskQueue queue;

    int threadCount;

    int shutdown;

} ThreadPool;

/* Thread Pool Functions */

void initializeThreadPool(ThreadPool *pool, int threadCount);

void submitTask(ThreadPool *pool, Task *task);

void shutdownThreadPool(ThreadPool *pool);

void *workerFunction(void *arg);

#endif
