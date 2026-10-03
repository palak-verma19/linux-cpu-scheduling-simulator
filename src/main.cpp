#include <iostream>
#include <vector>
#include <iomanip>
#include "../include/process.h"
#include <algorithm>

using namespace std;

// Function declarations
void fcfs(vector<Process>& processes);
void sjf(vector<Process>& processes);


// Display process performance
void displayPerformance(vector<Process>& processes) {

    cout << "\nPROCESS PERFORMANCE\n";
    cout << "-------------------------------------------------\n";

    cout << left
         << setw(8) << "PID"
         << setw(8) << "AT"
         << setw(8) << "BT"
         << setw(8) << "CT"
         << setw(8) << "TAT"
         << setw(8) << "WT"
         << setw(8) << "RT"
         << endl;

    for (const auto& p : processes) {

        cout << left
             << setw(8) << ("P" + to_string(p.pid))
             << setw(8) << p.arrivalTime
             << setw(8) << p.burstTime
             << setw(8) << p.completionTime
             << setw(8) << p.turnaroundTime
             << setw(8) << p.waitingTime
             << setw(8) << p.responseTime
             << endl;
    }
}


// Display Gantt Chart
void displayGanttChart(vector<Process>& processes, string algorithm) {

    // Sort processes according to completion time
    // This gives the actual execution order
    vector<Process> scheduled = processes;

    sort(scheduled.begin(), scheduled.end(),
         [](const Process& a, const Process& b) {
             return a.completionTime < b.completionTime;
         });

    cout << "\n\n" << algorithm << " GANTT CHART\n\n";

    cout << " ";

    for (const auto& p : scheduled) {
        cout << "---------";
    }

    cout << "\n|";

    for (const auto& p : scheduled) {
        cout << "   P" << p.pid << "   |";
    }

    cout << "\n ";

    for (const auto& p : scheduled) {
        cout << "---------";
    }

    cout << "\n";

    // Display timeline
    int startTime = 0;

    for (const auto& p : scheduled) {

        int executionStart = p.completionTime - p.burstTime;

        if (executionStart > startTime) {
            startTime = executionStart;
        }

        cout << startTime << "\t";

        startTime = p.completionTime;
    }

    cout << startTime << "\n";
}


// Display average performance
void displayAveragePerformance(vector<Process>& processes) {

    double totalWaitingTime = 0;
    double totalTurnaroundTime = 0;
    double totalResponseTime = 0;

    for (const auto& p : processes) {

        totalWaitingTime += p.waitingTime;
        totalTurnaroundTime += p.turnaroundTime;
        totalResponseTime += p.responseTime;
    }

    int n = processes.size();

    cout << "\nPERFORMANCE ANALYSIS\n";
    cout << "----------------------------\n";

    cout << fixed << setprecision(2);

    cout << "Average Waiting Time    : "
         << totalWaitingTime / n << endl;

    cout << "Average Turnaround Time : "
         << totalTurnaroundTime / n << endl;

    cout << "Average Response Time   : "
         << totalResponseTime / n << endl;
}


// Main function
int main() {

    cout << "========================================\n";
    cout << "   LINUX CPU SCHEDULING SIMULATOR\n";
    cout << "========================================\n";

    int n;

    cout << "\nEnter number of processes: ";
    cin >> n;

    vector<Process> processes(n);

    // Input process information
    for (int i = 0; i < n; i++) {

        processes[i].pid = i + 1;

        cout << "\nProcess P" << processes[i].pid << endl;

        cout << "Arrival Time: ";
        cin >> processes[i].arrivalTime;

        cout << "Burst Time: ";
        cin >> processes[i].burstTime;

        cout << "Priority: ";
        cin >> processes[i].priority;
    }


    // Select scheduling algorithm
    int choice;

    cout << "\n========================================\n";
    cout << "       SELECT SCHEDULING ALGORITHM\n";
    cout << "========================================\n";

    cout << "1. FCFS\n";
    cout << "2. SJF\n";

    cout << "\nEnter choice: ";
    cin >> choice;


    string algorithmName;


    if (choice == 1) {

        cout << "\nRunning FCFS Scheduling...\n";

        fcfs(processes);

        algorithmName = "FCFS";

    }
    else if (choice == 2) {

        cout << "\nRunning SJF Scheduling...\n";

        sjf(processes);

        algorithmName = "SJF";

    }
    else {

        cout << "\nInvalid choice!\n";

        return 0;
    }


    // Display results
    displayPerformance(processes);

    displayGanttChart(processes, algorithmName);

    displayAveragePerformance(processes);


    cout << "\n========================================\n";
    cout << "          SIMULATION COMPLETE\n";
    cout << "========================================\n";

    return 0;
}

