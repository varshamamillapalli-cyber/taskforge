#include <stdio.h>
#include "../include/task_manager.h"

void initializeTaskManager(TaskManager *manager)
{
    manager->waitingCount = 0;
    manager->runningCount = 0;
    manager->completedCount = 0;
}

void addWaitingTask(TaskManager *manager, Task *task)
{
    manager->waiting[manager->waitingCount++] = task;
}

void moveToRunning(TaskManager *manager, Task *task)
{
    manager->running[manager->runningCount++] = task;
}

void moveToCompleted(TaskManager *manager, Task *task)
{
    manager->completed[manager->completedCount++] = task;
}

void displayWaitingTasks(TaskManager *manager)
{
    printf("\n========== WAITING TASKS ==========\n");

    if(manager->waitingCount == 0)
    {
        printf("No Waiting Tasks\n");
        return;
    }

    for(int i=0;i<manager->waitingCount;i++)
    {
        printf("%d\t%s\n",
        manager->waiting[i]->taskID,
        manager->waiting[i]->taskName);
    }
}

void displayRunningTasks(TaskManager *manager)
{
    printf("\n========== RUNNING TASKS ==========\n");

    if(manager->runningCount == 0)
    {
        printf("No Running Tasks\n");
        return;
    }

    for(int i=0;i<manager->runningCount;i++)
    {
        printf("%d\t%s\n",
        manager->running[i]->taskID,
        manager->running[i]->taskName);
    }
}

void displayCompletedTasks(TaskManager *manager)
{
    printf("\n========== COMPLETED TASKS ==========\n");

    if(manager->completedCount == 0)
    {
        printf("No Completed Tasks\n");
        return;
    }

    for(int i=0;i<manager->completedCount;i++)
    {
        printf("%d\t%s\n",
        manager->completed[i]->taskID,
        manager->completed[i]->taskName);
    }
}
