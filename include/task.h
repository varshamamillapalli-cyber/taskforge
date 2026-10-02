#ifndef TASK_H
#define TASK_H

#include "common.h"

typedef struct Task
{
    int taskID;

    char taskName[MAX_TASK_NAME];

    TaskType taskType;

    int executionTime;

    TaskStatus status;

    int assignedWorker;

    struct Task *next;

} Task;

#endif
