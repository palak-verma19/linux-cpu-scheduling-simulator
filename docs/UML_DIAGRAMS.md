# UML Diagrams

## 1. Class/Data Structure Diagram

The project is primarily modular/procedural C++ rather than class-heavy object-oriented C++. The following diagram therefore models the central structures.

```mermaid
classDiagram
    class Process {
        +int pid
        +int arrivalTime
        +int burstTime
        +int priority
        +int completionTime
        +int turnaroundTime
        +int waitingTime
        +int responseTime
    }

    class GanttEntry {
        +int pid
        +int startTime
        +int endTime
    }

    class PerformanceMetrics {
        +double cpuUtilization
        +int contextSwitches
    }

    class AlgorithmResult {
        +string name
        +double averageWaitingTime
        +double averageTurnaroundTime
        +double averageResponseTime
        +double cpuUtilization
        +int contextSwitches
    }

    Process --> GanttEntry : execution represented by
    Process --> PerformanceMetrics : analyzed with
    AlgorithmResult --> PerformanceMetrics : contains
```

## 2. Sequence Diagram – Compare All

```mermaid
sequenceDiagram
    actor User
    participant Main as main.cpp
    participant Compare as comparison.cpp
    participant FCFS as fcfs.cpp
    participant SJF as sjf.cpp
    participant Priority as priority.cpp
    participant RR as round_robin.cpp
    participant Perf as performance.cpp

    User->>Main: Select Compare All
    Main->>Main: Read process data and quantum
    Main->>Compare: compareAlgorithms(processes, quantum)
    Compare->>FCFS: Run FCFS
    FCFS-->>Compare: Results + Gantt
    Compare->>Perf: Calculate metrics
    Perf-->>Compare: Metrics
    Compare->>SJF: Run SJF
    SJF-->>Compare: Results + Gantt
    Compare->>Perf: Calculate metrics
    Perf-->>Compare: Metrics
    Compare->>Priority: Run Priority
    Priority-->>Compare: Results + Gantt
    Compare->>Perf: Calculate metrics
    Perf-->>Compare: Metrics
    Compare->>RR: Run Round Robin
    RR-->>Compare: Results + Gantt
    Compare->>Perf: Calculate metrics
    Perf-->>Compare: Metrics
    Compare-->>Main: AlgorithmResult list
    Main-->>User: Comparison table
```

## 3. State Machine – Simulated Process

```mermaid
stateDiagram-v2
    [*] --> New
    New --> Ready : Arrival time reached
    Ready --> Running : Scheduler selects process
    Running --> Completed : Burst fully executed
    Running --> Ready : Preempted / quantum expires
    Completed --> [*]
```

### State Descriptions

| State | Meaning |
|---|---|
| New | Process exists but has not reached arrival time |
| Ready | Process is available for scheduling |
| Running | Process is assigned CPU time |
| Completed | Process has finished its burst |

Round Robin can return from Running to Ready when the quantum expires and burst time remains.
