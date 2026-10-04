#include <vector>

#include "comparison.h"
#include "performance.h"

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


// Run FCFS
AlgorithmResult runFCFS(
    const vector<Process>& original) {

    vector<Process> processes = original;
    vector<GanttEntry> gantt;

    fcfs(processes, gantt);

    PerformanceMetrics metrics =
        calculatePerformanceMetrics(
            processes,
            gantt);

    return {
        "FCFS",
        averageWaitingTime(processes),
        averageTurnaroundTime(processes),
        averageResponseTime(processes),
        metrics.cpuUtilization,
        metrics.contextSwitches
    };
}


// Run SJF
AlgorithmResult runSJF(
    const vector<Process>& original) {

    vector<Process> processes = original;
    vector<GanttEntry> gantt;

    sjf(processes, gantt);

    PerformanceMetrics metrics =
        calculatePerformanceMetrics(
            processes,
            gantt);

    return {
        "SJF",
        averageWaitingTime(processes),
        averageTurnaroundTime(processes),
        averageResponseTime(processes),
        metrics.cpuUtilization,
        metrics.contextSwitches
    };
}


// Run Priority Scheduling
AlgorithmResult runPriority(
    const vector<Process>& original) {

    vector<Process> processes = original;
    vector<GanttEntry> gantt;

    priorityScheduling(processes, gantt);

    PerformanceMetrics metrics =
        calculatePerformanceMetrics(
            processes,
            gantt);

    return {
        "Priority",
        averageWaitingTime(processes),
        averageTurnaroundTime(processes),
        averageResponseTime(processes),
        metrics.cpuUtilization,
        metrics.contextSwitches
    };
}


// Run Round Robin
AlgorithmResult runRoundRobin(
    const vector<Process>& original,
    int quantum) {

    vector<Process> processes = original;
    vector<GanttEntry> gantt;

    roundRobin(
        processes,
        quantum,
        gantt);

    PerformanceMetrics metrics =
        calculatePerformanceMetrics(
            processes,
            gantt);

    return {
        "Round Robin",
        averageWaitingTime(processes),
        averageTurnaroundTime(processes),
        averageResponseTime(processes),
        metrics.cpuUtilization,
        metrics.contextSwitches
    };
}


// Compare all algorithms
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
        runRoundRobin(
            processes,
            quantum));

    return results;
}
