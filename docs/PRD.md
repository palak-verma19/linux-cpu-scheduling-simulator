# Product Requirements Document (PRD)

## Product
Linux-Based CPU Scheduling Simulator and Process Performance Analyzer

## Vision
Provide a simple Linux-based learning and analysis tool for comparing CPU scheduling policies using the same process workload.

## Problem
Different scheduling policies affect waiting time, response time, turnaround time and context switching differently. Users need a practical way to observe and compare these effects.

## Target Users
- Operating Systems students
- Trainers
- Developers learning Linux/system programming

## Functional Requirements
1. Process input.
2. FCFS.
3. SJF.
4. Priority Scheduling.
5. Round Robin.
6. Gantt chart.
7. Process metrics.
8. CPU utilization.
9. Context switches.
10. Algorithm comparison.
11. Automated tests.
12. Linux character-device source.

## Non-Functional Requirements
- Linux-compatible simulator.
- C++17 application.
- C/Linux kernel module.
- Modular source.
- Repeatable GNU Make build.
- Git version control.
- Documented limitations.

## Deliverables
- Source code
- Tests
- Makefiles
- Linux driver
- README
- Stage documentation
- UML diagrams
- GitHub repository
- Final presentation

## Acceptance Criteria
The project is accepted when the scheduler builds successfully, automated tests pass, comparison works, documentation is available, and the Linux driver source demonstrates the required kernel concepts.
