// Name, etc
#define _GNU_SOURCE
#include <stdio.h>
#include <sched.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/resource.h>

// pinfo.c

int main(int argc, char* argv[]) {
    pid_t pid;
    int policy;
    int priority;
    if (argc > 1){
        pid = (pid_t)atoi(argv[1]);
    } else {
        pid = getpid();
    }

    errno = 0;
    priority = getpriority(PRIO_PROCESS, pid);
    if (errno != 0) {
        perror("getpriority failed");
        return 1;
    }

    policy = sched_getscheduler(pid);
    if (policy) {
        perror("sched_getschedular failed");
        return 1; 
    }
    printf("Process ID: %d\n", pid);
    printf("priority: %d\n", priority);

    switch (policy) {
        case SCHED_OTHER:
            printf("Scheduling Policy: SCHED_OTHER\n");
            break;
        case SCHED_FIFO:
            printf("Scheduling Policy: SCHED_FIFO\n");
            break;
        case SCHED_RR:
            printf("Scheduling Policy: SCHED_RR\n");
            break;
#ifdef SCHED_BATCH
        case SCHED_BATCH:
            printf("Scheduling Policy: SCHED_BATCH\n");
            break;
#endif
#ifdef SCHED_IDLE
        case SCHED_IDLE:
            printf("Scheduling Policy: SCHED_IDLE\n");
            break;
#endif
        default:
            printf("Scheduling Policy: Unknown %d\n", policy);
    }
    return 0;
}