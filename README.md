# Linux-Based CPU Scheduling Simulator and Process Performance Analyzer

## 1. Project Overview

The **Linux-Based CPU Scheduling Simulator and Process Performance Analyzer** is a C++17 application designed to simulate and compare common CPU scheduling algorithms used in Operating Systems.

The project demonstrates how different scheduling strategies affect process performance using measurable metrics such as:

- Waiting Time
- Turnaround Time
- Response Time
- Completion Time
- CPU Utilization
- Context Switches
- Gantt Chart

The project also includes a **Linux Character Device Driver** component to demonstrate Linux Kernel Module and User-Space/Kernel-Space communication concepts.

---

## 2. Objectives

The main objectives of this project are:

1. Implement common CPU scheduling algorithms.
2. Calculate important process scheduling metrics.
3. Visualize process execution using Gantt charts.
4. Compare scheduling algorithms based on performance.
5. Demonstrate Linux system programming concepts.
6. Demonstrate Linux Device Driver concepts using a character device.
7. Provide a modular and maintainable C++ project structure.
8. Provide automated tests for the scheduling algorithms.

---

## 3. Technologies Used

| Technology | Purpose |
|---|---|
| C++17 | CPU scheduling simulator |
| C | Linux kernel device driver |
| Linux / WSL2 | Development environment |
| GNU g++ | C++ compilation |
| GNU Make | Build automation |
| Linux Kernel Module | Device driver component |
| Character Device | User-space/kernel-space communication |
| Git & GitHub | Version control and project submission |

---

## 4. CPU Scheduling Algorithms

The simulator implements four scheduling algorithms.

### 4.1 First Come First Serve (FCFS)

FCFS schedules processes according to their arrival order.

Characteristics:

- Non-preemptive
- Simple implementation
- Easy to understand
- Can suffer from convoy effect

---

### 4.2 Shortest Job First (SJF)

SJF selects the available process with the shortest burst time.

Characteristics:

- Non-preemptive
- Usually provides low average waiting time
- Requires knowledge of burst time
- Long processes may experience starvation

---

### 4.3 Priority Scheduling

Priority Scheduling selects the available process with the highest priority.

In this project:

> Smaller priority number = Higher priority

Characteristics:

- Non-preemptive
- Useful when processes have different importance levels
- Lower-priority processes may experience starvation

---

### 4.4 Round Robin

Round Robin assigns each process a fixed time quantum.

Characteristics:

- Preemptive
- Suitable for time-sharing systems
- Provides better response time
- Number of context switches depends on the time quantum

---

## 5. Performance Metrics

The simulator calculates:

### Completion Time

The time at which a process finishes execution.

### Turnaround Time

```
Turnaround Time = Completion Time - Arrival Time
### Waiting Time
Waiting Time = Turnaround Time - Burst Time
### Response Time
Response Time = First CPU Start Time - Arrival Time

### CPU Utilization
CPU Utilization =
(Total CPU Busy Time / Total Elapsed Time) × 100

###Context Switches

A context switch is counted when consecutive Gantt chart entries belong to different processes.

### 6. Gantt Chart

The simulator generates a Gantt chart showing the execution sequence of processes.

Example:

| P1 | P2 | P3 | P1 | P4 |
0    2    4    6    8    10

For Round Robin, each time quantum execution is represented as a separate Gantt chart entry.

###7. Algorithm Comparison

The simulator provides an option to execute all four algorithms and compare:

Average Waiting Time
Average Turnaround Time
Average Response Time
CPU Utilization
Context Switches

The program also identifies the algorithm with the best:

Average Waiting Time
Average Turnaround Time
Average Response Time


### 8. Linux Device Driver Component

To satisfy the Linux Device Driver requirement of the capstone, the project contains a supporting Linux Character Device Driver.

Location:

linux_driver/

The driver source is:

linux_driver/cpu_scheduler_device.c

The driver demonstrates:

Linux Kernel Module
Character Device
Device number allocation
struct cdev
File operations
open()
read()
write()
release()
copy_to_user()
copy_from_user()
User-space/kernel-space communication
Device creation under /dev
Kernel logging

The intended device interface is:

/dev/cpu_scheduler
Driver Architecture
+--------------------------------+
| CPU Scheduling Simulator       |
|          User Space            |
+---------------+----------------+
                |
                | read / write
                v
+--------------------------------+
| /dev/cpu_scheduler             |
| Character Device               |
+---------------+----------------+
                |
                v
+--------------------------------+
| Linux Kernel Module            |
|          Kernel Space          |
+--------------------------------+

The driver is a supporting architecture component and does not prevent the CPU scheduling simulator from operating independently.

### 9. Project Structure
linux-cpu-scheduling-simulator/
│
├── include/
│   ├── process.h
│   ├── comparison.h
│   └── performance.h
│
├── src/
│   ├── main.cpp
│   ├── fcfs.cpp
│   ├── sjf.cpp
│   ├── priority.cpp
│   ├── round_robin.cpp
│   ├── comparison.cpp
│   └── performance.cpp
│
├── tests/
│   └── test_scheduler.cpp
│
├── linux_driver/
│   ├── cpu_scheduler_device.c
│   ├── Makefile
│   └── README.md
│
├── docs/
│
├── Makefile
├── README.md
└── .gitignore
### 10. Build Instructions
Prerequisites

Linux environment with:

g++
GNU Make
C++17 support

Check the compiler:

g++ --version

Check Make:

make --version
### 11. Build the Simulator

From the project root:

make

This creates the executable:

scheduler
### 12. Run the Simulator

Run:

./scheduler

or:

make run

The application provides a menu:

1. FCFS
2. SJF
3. Priority Scheduling
4. Round Robin
5. Compare All Algorithms
0. Exit
### 13. Run Automated Tests

The project contains an automated test suite covering:

FCFS
SJF
Priority Scheduling
Round Robin
Performance Metrics

Run:

make test

Expected result:

========================================
       CPU SCHEDULING TEST SUITE
========================================

[PASS] FCFS
[PASS] SJF
[PASS] Priority Scheduling
[PASS] Round Robin
[PASS] Performance Metrics

All tests passed.
### 14. Clean Build Files

To remove compiled object files, executable and test binary:

make clean
### 15. Linux Device Driver Build

The driver requires Linux kernel build headers matching the running kernel.

Normally:

cd linux_driver
make

The expected kernel module is:

cpu_scheduler_device.ko
WSL2 Limitation

The current development environment uses WSL2.

Current kernel:

6.6.87.2-microsoft-standard-WSL2

The matching kernel build directory is not available:

/lib/modules/6.6.87.2-microsoft-standard-WSL2/build

Therefore, kernel-module compilation and loading have not been performed in the current WSL2 environment.

The driver source is included as a genuine Linux character-device implementation and can be compiled in a suitable Linux kernel development environment with matching kernel headers.

Detailed instructions are available in:

linux_driver/README.md
### 16. Example Test Dataset

The following dataset can be used to demonstrate the simulator:

Process	Arrival Time	Burst Time	Priority
P1	0	5	2
P2	1	3	1
P3	2	8	3
P4	3	2	2

For Round Robin:

Time Quantum = 2
### 17. Sample Comparison Result

Using the example dataset:

Algorithm	Avg WT	Avg TAT	Avg RT	CPU Util.	Context Switches
FCFS	5.75	10.25	5.75	100%	3
SJF	4.00	8.50	4.00	100%	3
Priority	4.25	8.75	4.25	100%	3
Round Robin	7.25	11.75	2.00	100%	8
Observation
SJF provides the lowest average waiting time.
SJF provides the lowest average turnaround time.
Round Robin provides the lowest average response time.
Round Robin produces more context switches because processes are preempted after the time quantum.
### 18. Software Architecture

The project follows a modular architecture.

                    +------------------+
                    |   main.cpp       |
                    | User Interface   |
                    +--------+---------+
                             |
              +--------------+--------------+
              |              |              |
              v              v              v
          +-------+      +-------+      +----------+
          | FCFS  |      |  SJF  |      | Priority |
          +-------+      +-------+      +----------+
              \              |              /
               \             |             /
                +------------+------------+
                             |
                             v
                    +----------------+
                    | Round Robin    |
                    +-------+--------+
                            |
                            v
                  +----------------------+
                  | Performance Analyzer |
                  +----------+-----------+
                             |
                             v
                  +----------------------+
                  | Comparison Module    |
                  +----------------------+

Linux Device Driver Component
              |
              v
     +--------------------+
     | Character Device   |
     | /dev/cpu_scheduler |
     +--------------------+
              |
              v
     +--------------------+
     | Linux Kernel       |
     | Character Driver  |
     +--------------------+
### 19. Design Principles

The project follows:

Modular programming
Separation of concerns
Reusable data structures
Function-based algorithm implementation
Automated testing
Linux system programming concepts
Kernel/user-space separation
Build automation using Make
### 20. Testing Status

The automated test suite has been executed successfully.

FCFS                 PASS
SJF                  PASS
Priority Scheduling  PASS
Round Robin          PASS
Performance Metrics  PASS

All implemented scheduler tests passed successfully.

### 21. Limitations
The simulator is a discrete scheduling simulation and does not create real operating-system processes.
Scheduling decisions are simulated in user space.
The Linux device driver requires a compatible Linux kernel development environment for compilation and loading.
The current WSL2 environment does not contain matching kernel build headers.
The project does not attempt to replace or modify the host operating system scheduler.
### 22. Future Enhancements

Possible future improvements include:

Preemptive SJF
Preemptive Priority Scheduling
Aging to prevent starvation
Dynamic process creation
File-based input
Exporting results to CSV
Graphical Gantt chart
Real-time scheduling algorithms
Integration with additional Linux kernel interfaces
Extended character-device communication
### 23. Conclusion

This project demonstrates the implementation and comparison of fundamental CPU scheduling algorithms while incorporating Linux system programming and Device Driver concepts.

The simulator provides measurable performance analysis through waiting time, turnaround time, response time, CPU utilization and context switches.

The supporting Linux character device demonstrates the interaction between user space and kernel space, making the project suitable for demonstrating both Software Architecture and Linux Device Driver concepts.

###24. Author

Palak Verma

Project: Linux-Based CPU Scheduling Simulator and Process Performance Analyzer

Technology: C++17, C, Linux, GNU Make, Linux Kernel Module
