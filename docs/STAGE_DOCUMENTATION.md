# Linux-Based CPU Scheduling Simulator and Process Performance Analyzer
# Stage 1–6 Project Documentation

## Stage 1 – Project Introduction

### Project Title
Linux-Based CPU Scheduling Simulator and Process Performance Analyzer

### Problem Statement
CPU scheduling determines which ready process receives CPU time. Different scheduling policies produce different waiting time, response time, turnaround time and context-switch behavior. This project provides a practical Linux-based simulator for comparing these effects using the same workload.

### Objectives
- Implement FCFS, SJF, Priority and Round Robin.
- Generate Gantt-chart execution sequences.
- Calculate completion, turnaround, waiting and response time.
- Calculate CPU utilization and context switches.
- Compare algorithms.
- Provide automated tests.
- Demonstrate Linux character-device and kernel-module concepts.

### Scope
The simulator is a user-space scheduling simulation. It does not replace the actual Linux scheduler or create a complete hardware emulator. A supporting Linux character-device driver demonstrates kernel/user-space concepts.

### Expected Outcome
A user can enter process information, run an algorithm, view its execution sequence and metrics, and compare all algorithms.

---

## Stage 2 – Project Requirements & Development Plan

### Functional Requirements

| ID | Requirement |
|---|---|
| FR-01 | Accept process ID, arrival time, burst time and priority. |
| FR-02 | Execute FCFS. |
| FR-03 | Execute SJF. |
| FR-04 | Execute Priority Scheduling. |
| FR-05 | Execute Round Robin with configurable quantum. |
| FR-06 | Generate Gantt entries. |
| FR-07 | Calculate completion time. |
| FR-08 | Calculate turnaround time. |
| FR-09 | Calculate waiting time. |
| FR-10 | Calculate response time. |
| FR-11 | Calculate CPU utilization. |
| FR-12 | Calculate context switches. |
| FR-13 | Compare algorithms. |
| FR-14 | Run automated tests. |
| FR-15 | Provide Linux character-device driver source. |

### Non-Functional Requirements
- Linux/WSL2 compatible for the simulator.
- C++17 for the simulator.
- C/Linux kernel APIs for the driver.
- Modular and readable source.
- Repeatable GNU Make build.
- Git/GitHub version control.
- Documented limitations.

### Major Modules
1. User Interface
2. Process Data Model
3. FCFS
4. SJF
5. Priority
6. Round Robin
7. Performance Analyzer
8. Comparison Module
9. Automated Test Suite
10. Linux Character Device Driver

### Development Plan

| Stage | Planned Work | Evidence |
|---|---|---|
| 1 | Problem, objective and scope | This document |
| 2 | Requirements and modules | PRD section |
| 3 | Architecture, data structures, UML | Architecture/UML section |
| 4 | Core implementation | Git history/source |
| 5 | Testing and improvements | Test results |
| 6 | Final delivery and presentation | GitHub/final demo |

### PRD Acceptance Criteria
The project is accepted when the scheduler builds successfully, automated tests pass, comparison works, documentation is present, and the Linux driver source demonstrates the required kernel concepts.

---

## Stage 3 – System Design & Architecture

### High-Level Architecture

```text
+-----------------------------+
|        User Interface       |
|          main.cpp           |
+-------------+---------------+
              |
              v
+-----------------------------+
|     Scheduling Modules      |
| FCFS | SJF | Priority | RR |
+-------------+---------------+
              |
              v
+-----------------------------+
|      Gantt / Process Data   |
+-------------+---------------+
              |
              v
+-----------------------------+
|     Performance Analyzer    |
| WT | TAT | RT | CPU | CS  |
+-------------+---------------+
              |
              v
+-----------------------------+
|     Comparison Module       |
+-----------------------------+

Supporting Linux Component:

User Space
    |
    | read/write
    v
/dev/cpu_scheduler
    |
    v
Linux Character Device
    |
    v
Kernel Module
```

### Major Components

**main.cpp** – command-line interface.

**process.h** – `Process` and `GanttEntry` structures.

**Scheduling modules** – implement individual scheduling policies.

**performance.cpp** – CPU utilization and context-switch analysis.

**comparison.cpp** – runs algorithms independently and compares results.

**test_scheduler.cpp** – automated verification.

**cpu_scheduler_device.c** – supporting Linux character-device kernel module.

### Core Data Structures

```text
Process
├── pid
├── arrivalTime
├── burstTime
├── priority
├── completionTime
├── turnaroundTime
├── waitingTime
└── responseTime

GanttEntry
├── pid
├── startTime
└── endTime
```

### Computer Architecture Relationship

The project does not emulate CPU hardware. It models software-level CPU scheduling concepts that operate above the processor:

```text
Processes
   ↓
Operating System Scheduler
   ↓
CPU Allocation
   ↓
Processor Hardware
```

The project demonstrates CPU time allocation, process execution, context switching as a scheduling concept, and kernel/user-space separation.

### Hardware–Software Relationship

```text
Application Software
       ↓
Operating System
       ↓
Kernel Interface / Driver
       ↓
Hardware-oriented Kernel Services
```

### Linux Device Driver Architecture

The driver is designed as:

```text
User Application
      |
      | read/write
      v
/dev/cpu_scheduler
      |
      v
Character Device
      |
      v
Linux Kernel Module
```

### Implementation Plan
1. Define process structures.
2. Implement FCFS.
3. Implement SJF.
4. Implement Priority.
5. Implement Round Robin.
6. Add Gantt chart.
7. Add performance analysis.
8. Add comparison.
9. Add automated tests.
10. Add Linux driver source.
11. Document limitations and results.

---

## Stage 4 – Initial Implementation & Prototype

### Implemented Modules

- FCFS – non-preemptive arrival-order scheduling.
- SJF – non-preemptive shortest available burst.
- Priority – non-preemptive; smaller number means higher priority.
- Round Robin – ready queue with configurable time quantum.
- Gantt chart generation.
- Performance metrics.
- Algorithm comparison.
- Automated tests.
- Linux character-device source.

### Driver Concepts
The driver demonstrates:
- Linux kernel module.
- Character-device registration.
- Device-number allocation.
- `struct cdev`.
- File operations.
- `open`, `read`, `write`, `release`.
- `copy_to_user` and `copy_from_user`.
- Device creation.
- Kernel logging.

### Development Issue
The current WSL2 kernel is:

```text
6.6.87.2-microsoft-standard-WSL2
```

The matching build directory is unavailable:

```text
/lib/modules/6.6.87.2-microsoft-standard-WSL2/build
```

### Solution
The driver source was retained as a genuine Linux implementation and its compilation/loading requirement was documented. The WSL kernel was not replaced close to the deadline.

---

## Stage 5 – Testing, Integration & Improvement

### Test Dataset

| Process | Arrival | Burst | Priority |
|---|---:|---:|---:|
| P1 | 0 | 5 | 2 |
| P2 | 1 | 3 | 1 |
| P3 | 2 | 8 | 3 |
| P4 | 3 | 2 | 2 |

Round Robin quantum: `2`

### Automated Test Results

```text
[PASS] FCFS
[PASS] SJF
[PASS] Priority Scheduling
[PASS] Round Robin
[PASS] Performance Metrics

All tests passed.
```

### Sample Comparison

| Algorithm | Avg WT | Avg TAT | Avg RT | CPU Utilization | Context Switches |
|---|---:|---:|---:|---:|---:|
| FCFS | 5.75 | 10.25 | 5.75 | 100% | 3 |
| SJF | 4.00 | 8.50 | 4.00 | 100% | 3 |
| Priority | 4.25 | 8.75 | 4.25 | 100% | 3 |
| Round Robin | 7.25 | 11.75 | 2.00 | 100% | 8 |

### Observations
- SJF gives the lowest average waiting time for this workload.
- SJF gives the lowest average turnaround time for this workload.
- Round Robin gives the lowest average response time for this workload.
- Round Robin produces more context switches because of time-slice preemption.

### Improvements
The project was progressively improved with:
- Make-based build system.
- Algorithm comparison.
- CPU utilization.
- Context-switch analysis.
- Automated testing.
- Linux driver source.
- Documentation.

### Testing Levels
**Unit:** scheduling functions tested against known expected results.

**Integration:** scheduling modules, Gantt data and performance analyzer compiled and executed together.

**System:** complete command-line application built and exercised through its menu.

---

## Stage 6 – Final Implementation & Presentation

### Final Features
- FCFS
- SJF
- Priority
- Round Robin
- Gantt chart
- Completion time
- Turnaround time
- Waiting time
- Response time
- CPU utilization
- Context switches
- Algorithm comparison
- Automated tests
- Linux character-device source
- GNU Make
- Git/GitHub
- Documentation

### Final Validation

```bash
make clean
make
make test
```

All five automated test groups passed.

### GitHub

https://github.com/palak-verma19/linux-cpu-scheduling-simulator

### Recommended 5–10 Minute Presentation
1. Introduction and problem.
2. Architecture.
3. Run one scheduling algorithm.
4. Demonstrate Compare All.
5. Explain metrics.
6. Run `make test`.
7. Explain Linux character driver.
8. State WSL2 driver limitation honestly.
9. Show GitHub.
10. Explain limitations and future work.

### Achievements
The project demonstrates Operating Systems concepts, CPU scheduling, C++ programming, Linux programming, software architecture, kernel/user-space concepts, character-device structure, automated testing and Git-based development.

### Limitations
- User-space simulation; does not replace the Linux scheduler.
- Driver not loaded in current WSL2 environment because matching headers are unavailable.
- Hardware behavior is represented conceptually rather than by hardware emulation.
- Results depend on the workload.

### Future Improvements
- Preemptive SJF.
- Preemptive Priority.
- Aging.
- File-based input.
- CSV export.
- Graphical Gantt chart.
- Additional Linux kernel interfaces.
- Driver/user-space reporting integration.

---

# Progress Evidence

The repository history provides development evidence:

```text
098d66b Add project build system
6403b98 Add algorithm performance comparison
64552d2 Add CPU utilization and context switch analysis
bbcbaa6 Add automated test suite and test build target
e71b3f2 Complete Linux CPU scheduling capstone
```

Useful evidence commands:

```bash
git log --oneline --decorate
git status
git show --stat <commit>
make clean
make
make test
```
