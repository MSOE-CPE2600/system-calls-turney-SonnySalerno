# Lab 9 System Calls
**Author:** Sonny Salerno
 
**Course:** CPE 2600 111 

---

## Overview
This lab introduces the use of POSIX system calls to interact directly with the operating system.

--- 

info.c: Displays detailed system information like time, hostname, OS details, CPU count, and memory usage.

pinfo.c: Prints information about a specific processes (PID) including scheduling policy and priority.

pmod.c: Modifies its own process priority and suspends executions for a specific nanosecond interval.

finfo.c: Displays information about a file, including type, permissions, size, owner, and modification time.

---

## To build
```bash
make clean
```
```bash
make
```

## To run
```bash
./info
```
```bash
./pinfo [pid]
```
```bash
./pmod
```
```bash
./finfo "filename"
```