#ifndef TASK_MANAGER_H
#define TASK_MANAGER_H

#include "task.h"

#define MAX_TASKS 100

typedef struct
{
    Task *waiting[MAX_TASKS];
    Task *running[MAX_TASKS];
    Task *completed[MAX_TASKS];

    int waitingCount;
    int runningCount;
    int completedCount;

} TaskManager;

void initializeTaskManager(TaskManager *manager);

void addWaitingTask(TaskManager *manager, Task *task);

void moveToRunning(TaskManager *manager, Task *task);

void moveToCompleted(TaskManager *manager, Task *task);

void displayWaitingTasks(TaskManager *manager);

void displayRunningTasks(TaskManager *manager);

void displayCompletedTasks(TaskManager *manager);

#endif
