// Name, etc
#include <stdio.h>
#include <unistd.h>
#include <time.h>
// pmod.c

int main(int argc, char* argv[])
{
    int new_nice_value;
    new_nice_value = nice(10);

    printf("Priority reduced by 10. New nice value is %d\n", new_nice_value);

    struct timespec ts;
    ts.tv_sec = 1;
    ts.tv_nsec = 837272638;

    printf("Sleeping for 1,837,272,638 nanoseconds\n");
    if (nanosleep(&ts, NULL) == -1) {
        perror("nanosleep");
        return 1;
    }
    printf("Process completed!\n");
    return 0;
}