#ifndef PROCESS_H
#define PROCESS_H

struct Process {
    int pid;
    int arrivalTime;
    int burstTime;
    int priority;

    int completionTime;
    int turnaroundTime;
    int waitingTime;
    int responseTime;
};

struct GanttEntry {
    int pid;
    int startTime;
    int endTime;
};

#endif
