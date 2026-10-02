#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/thread_pool.h"

int taskCounter = 1;
int totalSubmitted = 0;
int totalCompleted = 0;

void displayMenu()
{
    printf("\n");
    printf("=============================================================\n");
    printf("              TASKFORGE v1.0\n");
    printf("      Intelligent Thread Pool Task Engine\n");
    printf("=============================================================\n");

    printf("Operating System : Ubuntu Linux\n");
    printf("Thread Pool      : ACTIVE\n");
    printf("Worker Threads   : %d\n", MAX_THREADS);
    printf("Scheduling       : FIFO Queue\n");

    printf("=============================================================\n");
    printf("1. Submit New Task\n");
    printf("2. View Task Queue\n");
    printf("3. View Statistics\n");
    printf("4. About Project\n");
    printf("5. Exit\n");
    printf("=============================================================\n");
    printf("Enter Choice : ");
}

void displayStatistics()
{
    printf("\n");
    printf("=====================================================\n");
    printf("                 TASK STATISTICS\n");
    printf("=====================================================\n");
    printf("Total Submitted Tasks : %d\n", totalSubmitted);
    printf("Completed Tasks       : %d\n", totalCompleted);
    printf("Worker Threads        : %d\n", MAX_THREADS);
    printf("Scheduling Policy     : FIFO\n");
    printf("=====================================================\n");
}

void aboutProject()
{
    printf("\n");
    printf("=====================================================\n");
    printf("                 ABOUT TASKFORGE\n");
    printf("=====================================================\n");
    printf("Project Name : TaskForge\n");
    printf("Project Type : Intelligent Thread Pool Task Engine\n");
    printf("Platform     : Ubuntu Linux\n");
    printf("Language     : C\n");
    printf("Compiler     : GCC\n");
    printf("Thread Library : POSIX pthread\n\n");

    printf("Features\n");
    printf("--------\n");
    printf("- Thread Pool\n");
    printf("- FIFO Task Queue\n");
    printf("- Worker Threads\n");
    printf("- Multithreading\n");
    printf("- Synchronization\n");
    printf("- Dynamic Memory Allocation\n");
    printf("=====================================================\n");
}

int main()
{
    ThreadPool pool;

    initializeThreadPool(&pool, MAX_THREADS);

    int choice;

    while (1)
    {
        displayMenu();

        scanf("%d", &choice);

        switch (choice)
        {
            case 1:
            {
                Task *task = (Task *)malloc(sizeof(Task));

                task->taskID = taskCounter++;

                printf("\nEnter Task Name : ");
                scanf(" %[^\n]", task->taskName);

                printf("\nTask Type\n");
                printf("1. CPU Task\n");
                printf("2. IO Task\n");
                printf("3. Simulation Task\n");

                printf("Enter Choice : ");
                scanf("%d", (int *)&task->taskType);

                printf("Execution Time (seconds): ");
                scanf("%d", &task->executionTime);

                task->status = WAITING;
                task->next = NULL;

                submitTask(&pool, task);

                totalSubmitted++;

                printf("\nTask Submitted Successfully.\n");

                break;
            }

            case 2:

                displayQueue(&pool.queue);

                break;

            case 3:

                displayStatistics();

                break;

            case 4:

                aboutProject();

                break;

            case 5:

                shutdownThreadPool(&pool);

                printf("\nThank you for using TaskForge.\n");

                return 0;

            default:

                printf("\nInvalid Choice.\n");
        }
    }
}
