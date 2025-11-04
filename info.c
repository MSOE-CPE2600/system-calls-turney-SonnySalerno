/*******************************************************************
* Filename: info.c
* Description: POSIX info sys calls. Displays current sys info 
* time, hostname, os details, CPU count, and mem.
* Author: Sonny Salerno
* Course: CPE2600 111
* Date: 11/03/2025
* Note: to run this make clean, make, ./info
*********************************************************************/
#include <stdio.h>
#include <time.h>
#include <unistd.h> 
#include <sys/utsname.h>
#include <sys/sysinfo.h>
#include <stdlib.h>
// info.c

int main(int argc, char* argv[]) {
    struct timespec ts; // used by clock_gettime()
    struct utsname system_info; // holds sys info
    // clock_gettime(): retrieves the current sys time
    // CLOCK_REALTIME gives wall clock time from epoch
    if (clock_gettime(CLOCK_REALTIME, &ts) == -1) {
        perror("colock_gettime");
        return 1;
    }
    // convert to nanoseconds for easier display
    long long total_nano = (long long)ts.tv_sec * 1000000000LL + ts.tv_nsec;
    printf("Current time of day: %lld\n", total_nano);
    // gethostname(): gets the network hostname of sys
    char hostname[256];
    if (gethostname(hostname, sizeof(hostname)) == 0 && hostname[0] != '\0') {
        printf("System Network Name: %s\n", hostname);
    } else {
        perror("gethostname");
    }
    // uname(): fills a struct with sys info
    if (uname(&system_info) == -1) {
        perror("uname");
        return 1;
    }
    if (system_info.sysname[0] != '\0')
        printf("Operating System Name: %s\n", system_info.sysname);
    if (system_info.release[0] != '\0')
        printf("Operating System Release: %s\n", system_info.release);
    if (system_info.version[0] != '\0')
        printf("Operating System Version: %s\n", system_info.version);
    if (system_info.machine[0] != '\0')
        printf("System Hardware Type: %s\n", system_info.machine);
    
    // get_nprocs(): returns the number of active CPUs 
    int num_cpus = get_nprocs();
    printf("Number of CPUs: %d\n", num_cpus);
    // getpagesize(): return size of a memory page in bytes
    long page_size = getpagesize();
    // sysconf(): retrieves sys config like total and free pages
    long total_pages = sysconf(_SC_PHYS_PAGES);
    long free_pages = sysconf(_SC_AVPHYS_PAGES);

    if (total_pages == -1 || free_pages == -1) {
        perror("sysconf");
        return 1;
    }
    // calcs mem size
    long long total_mem = (long long)total_pages * page_size;
    long long free_mem = (long long)free_pages * page_size; 

    printf("Total Physical Memory: %lld bytes\n", total_mem);
    printf("Free Physical Memory: %lld bytes\n", free_mem);


    return 0;
}