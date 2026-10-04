#include <vector>
#include "comparison.h"

using namespace std;

// Function declarations
void fcfs(vector<Process>& processes,
          vector<GanttEntry>& gantt);

void sjf(vector<Process>& processes,
         vector<GanttEntry>& gantt);

void priorityScheduling(vector<Process>& processes,
                         vector<GanttEntry>& gantt);

void roundRobin(vector<Process>& processes,
                int quantum,
                vector<GanttEntry>& gantt);


// Calculate average waiting time
double averageWaitingTime(
    const vector<Process>& processes) {

    double total = 0;

    for (const auto& p : processes) {
        total += p.waitingTime;
    }

    return total / processes.size();
}


// Calculate average turnaround time
double averageTurnaroundTime(
    const vector<Process>& processes) {

    double total = 0;

    for (const auto& p : processes) {
        total += p.turnaroundTime;
    }

    return total / processes.size();
}


// Calculate average response time
double averageResponseTime(
    const vector<Process>& processes) {

    double total = 0;

    for (const auto& p : processes) {
        total += p.responseTime;
    }

    return total / processes.size();
}


// Run FCFS on a copy of the original processes
AlgorithmResult runFCFS(
    const vector<Process>& original) {

    vector<Process> processes = original;
    vector<GanttEntry> gantt;

    fcfs(processes, gantt);

    return {
        "FCFS",
        averageWaitingTime(processes),
        averageTurnaroundTime(processes),
        averageResponseTime(processes)
    };
}


// Run SJF on a copy of the original processes
AlgorithmResult runSJF(
    const vector<Process>& original) {

    vector<Process> processes = original;
    vector<GanttEntry> gantt;

    sjf(processes, gantt);

    return {
        "SJF",
        averageWaitingTime(processes),
        averageTurnaroundTime(processes),
        averageResponseTime(processes)
    };
}


// Run Priority Scheduling on a copy
AlgorithmResult runPriority(
    const vector<Process>& original) {

    vector<Process> processes = original;
    vector<GanttEntry> gantt;

    priorityScheduling(processes, gantt);

    return {
        "Priority",
        averageWaitingTime(processes),
        averageTurnaroundTime(processes),
        averageResponseTime(processes)
    };
}


// Run Round Robin on a copy
AlgorithmResult runRoundRobin(
    const vector<Process>& original,
    int quantum) {

    vector<Process> processes = original;
    vector<GanttEntry> gantt;

    roundRobin(processes, quantum, gantt);

    return {
        "Round Robin",
        averageWaitingTime(processes),
        averageTurnaroundTime(processes),
        averageResponseTime(processes)
    };
}


// Compare all scheduling algorithms
vector<AlgorithmResult> compareAlgorithms(
    const vector<Process>& processes,
    int quantum) {

    vector<AlgorithmResult> results;

    results.push_back(
        runFCFS(processes));

    results.push_back(
        runSJF(processes));

    results.push_back(
        runPriority(processes));

    results.push_back(
        runRoundRobin(processes, quantum));

    return results;
}
