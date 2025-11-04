/*******************************************************************
* Filename: pmod.c
* Description: process contol using nice() and nanosleep() sys calls. 
* The process lowers its priority and sleeps for a specific time
* Author: Sonny Salerno
* Course: CPE2600 111
* Date: 11/03/2025
* Note: to run this make clean, make, ./pmod
*********************************************************************/
#include <stdio.h>
#include <unistd.h>
#include <time.h>
// pmod.c

int main(int argc, char* argv[]) {
    // nice(): adjusts the process priority
    int new_nice_value;
    new_nice_value = nice(10);
    printf("Priority reduced by 10. New nice value is %d\n", new_nice_value);

    // nanosleep(): suspends the process for a specific time
    // a struct with seconds and nanoseocnds
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