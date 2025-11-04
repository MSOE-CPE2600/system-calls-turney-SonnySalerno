/*******************************************************************
* Filename: finfo.c
* Description: Displays detailed file info like type, permission, 
* owner, size, and modification time using stat()
* Author: Sonny Salerno
* Course: CPE2600 111
* Date: 11/03/2025
* Note: to run this make clean, make, ./finfo (e.g filename.txt)
*********************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>
#include <time.h>
// finfo.c
// helper function to print readable file perms
void print_permissions(mode_t mode);

int main(int argc, char* argv[]) {
    struct stat fileStat;   // holds file info
    if (argc != 2) {
        fprintf(stderr, "Usage: %s 'filename'\n",argv[0]);
        return 1;
    }
    // stat(): gets file status info for file
    if (stat(argv[1], &fileStat) == -1) {
        perror("stat");
        return 1;
    }

    printf("File: %s\n", argv[1]);
    // identifies and prints file 
    printf("Type: ");
    if (S_ISREG(fileStat.st_mode))
        printf("Regular File\n");
    else if (S_ISDIR(fileStat.st_mode))
        printf("Directory\n");
    else if (S_ISLNK(fileStat.st_mode))
        printf("Symbolic Link\n");
    else if (S_ISCHR(fileStat.st_mode))
        printf("Character Device\n");
    else if (S_ISBLK(fileStat.st_mode))
        printf("Block Device\n");
    else if (S_ISFIFO(fileStat.st_mode))
        printf("FIFO / Pipe\n");
    else if (S_ISSOCK(fileStat.st_mode))
        printf("Socket\n");
    else
        printf("Unknown\n");
    
    printf("Permissions: ");
    print_permissions(fileStat.st_mode);
    // st_uid gives the numeric user ID of the owner
    printf("Owner UID: %d\n", fileStat.st_uid);
    // st_size gives the file size in bytes
    printf("Size: %11lld bytes\n", (long long)fileStat.st_size);
    // st_mtime gives the last modification time
    char *mod_time = ctime(&fileStat.st_mtime);
    if (mod_time != NULL) {
        printf("Last Modified: %s", mod_time);
    } else { 
        printf("Last Modified: N/A\n");
    }
    return 0;
}

void print_permissions(mode_t mode) {
    char perms[10];
    perms[0] = (mode & S_IRUSR) ? 'r' : '-';
    perms[1] = (mode & S_IWUSR) ? 'w' : '-';
    perms[2] = (mode & S_IXUSR) ? 'x' : '-';
    perms[3] = (mode & S_IRGRP) ? 'r' : '-';
    perms[4] = (mode & S_IWGRP) ? 'w' : '-';
    perms[5] = (mode & S_IXGRP) ? 'x' : '-';
    perms[6] = (mode & S_IROTH) ? 'r' : '-';
    perms[7] = (mode & S_IWOTH) ? 'w' : '-';
    perms[8] = (mode & S_IXOTH) ? 'x' : '-';
    perms[9] = '\0';
    printf("%s\n", perms);
}