#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

#include "../include/thread_pool.h"

extern int totalCompleted;

/* Worker Thread Function */

void *workerFunction(void *arg)
{
    ThreadPool *pool = (ThreadPool *)arg;

    while (!pool->shutdown)
    {
        Task *task = dequeueTask(&pool->queue);

        if (task == NULL)
            continue;

        task->status = RUNNING;

        printf("\n=====================================================\n");
        printf("Worker ID       : %lu\n", (unsigned long)pthread_self());
        printf("Task ID         : %d\n", task->taskID);
        printf("Task Name       : %s\n", task->taskName);

        switch (task->taskType)
        {
            case CPU_TASK:
                printf("Task Type       : CPU Intensive\n");
                break;

            case IO_TASK:
                printf("Task Type       : IO Intensive\n");
                break;

            case SIMULATION_TASK:
                printf("Task Type       : Simulation\n");
                break;
        }

        printf("Status          : RUNNING\n");
        printf("Execution Time  : %d Seconds\n", task->executionTime);
        printf("-----------------------------------------------------\n");

        sleep(task->executionTime);

        task->status = COMPLETED;

        totalCompleted++;

        printf("Task %d Completed Successfully.\n", task->taskID);
        printf("Status          : COMPLETED\n");
        printf("=====================================================\n");

        free(task);
    }

    pthread_exit(NULL);
}

/* Initialize Thread Pool */

void initializeThreadPool(ThreadPool *pool, int threadCount)
{
    pool->threadCount = threadCount;
    pool->shutdown = 0;

    initializeQueue(&pool->queue);

    printf("\n=====================================================\n");
    printf("Initializing Thread Pool...\n");
    printf("Creating %d Worker Threads\n", threadCount);
    printf("=====================================================\n");

    for (int i = 0; i < threadCount; i++)
    {
        if (pthread_create(&pool->workers[i],
                           NULL,
                           workerFunction,
                           pool) != 0)
        {
            printf("Failed to create Worker %d\n", i + 1);
            exit(EXIT_FAILURE);
        }

        printf("Worker-%d Created Successfully\n", i + 1);
    }

    printf("=====================================================\n");
    printf("Thread Pool Initialization Complete\n");
    printf("=====================================================\n");
}

/* Submit Task */

void submitTask(ThreadPool *pool, Task *task)
{
    enqueueTask(&pool->queue, task);

    printf("\nTask %d Submitted Successfully.\n", task->taskID);
}

/* Shutdown Thread Pool */

void shutdownThreadPool(ThreadPool *pool)
{
    printf("\n=====================================================\n");
    printf("Shutting Down Thread Pool...\n");
    printf("=====================================================\n");

    pool->shutdown = 1;

    pthread_cond_broadcast(&pool->queue.condition);

    for (int i = 0; i < pool->threadCount; i++)
    {
        pthread_join(pool->workers[i], NULL);
    }

    destroyQueue(&pool->queue);

    printf("All Worker Threads Terminated Successfully.\n");
    printf("Thread Pool Shutdown Complete.\n");
    printf("=====================================================\n");
}
