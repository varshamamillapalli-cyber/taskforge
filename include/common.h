#ifndef COMMON_H
#define COMMON_H

#define MAX_THREADS 4
#define MAX_TASK_NAME 50

typedef enum {
    CPU_TASK = 1,
    IO_TASK,
    SIMULATION_TASK
} TaskType;

typedef enum {
    WAITING = 1,
    RUNNING,
    COMPLETED
} TaskStatus;

#endif
