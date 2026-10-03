#include <iostream>
#include <vector>
#include "../include/process.h"

using namespace std;

// FCFS function
void fcfs(vector<Process>& processes);

// Display Gantt Chart
void displayGanttChart(const vector<Process>& processes) {

    cout << "\n\nFCFS GANTT CHART\n\n";

    cout << " ";

    for (const auto& p : processes) {
        cout << "--------";
    }

    cout << "-\n";

    cout << "|";

    for (const auto& p : processes) {
        cout << "   P" << p.pid << "   |";
    }

    cout << "\n ";

    for (const auto& p : processes) {
        cout << "--------";
    }

    cout << "-\n";

    cout << "0";

    for (const auto& p : processes) {
        cout << "\t" << p.completionTime;
    }

    cout << "\n";
}

// Display performance metrics
void displayPerformance(const vector<Process>& processes) {

    double totalWaiting = 0;
    double totalTurnaround = 0;
    double totalResponse = 0;

    for (const auto& p : processes) {
        totalWaiting += p.waitingTime;
        totalTurnaround += p.turnaroundTime;
        totalResponse += p.responseTime;
    }

    int n = processes.size();

    cout << "\nPERFORMANCE ANALYSIS\n";
    cout << "----------------------------\n";

    cout << "Average Waiting Time    : "
         << totalWaiting / n << endl;

    cout << "Average Turnaround Time : "
         << totalTurnaround / n << endl;

    cout << "Average Response Time   : "
         << totalResponse / n << endl;
}

int main() {

    int n;

    cout << "========================================\n";
    cout << "   LINUX CPU SCHEDULING SIMULATOR\n";
    cout << "========================================\n\n";

    cout << "Enter number of processes: ";
    cin >> n;

    vector<Process> processes(n);

    // Take process information
    for (int i = 0; i < n; i++) {

        processes[i].pid = i + 1;

        cout << "\nProcess P" << i + 1 << endl;

        cout << "Arrival Time: ";
        cin >> processes[i].arrivalTime;

        cout << "Burst Time: ";
        cin >> processes[i].burstTime;

        cout << "Priority: ";
        cin >> processes[i].priority;
    }

    // Run FCFS
    cout << "\n\nRunning FCFS Scheduling...\n";

    fcfs(processes);

    // Display process results
    cout << "\nPROCESS PERFORMANCE\n";
    cout << "-------------------------------------------------\n";

    cout << "PID\tAT\tBT\tCT\tTAT\tWT\tRT\n";

    for (const auto& p : processes) {

        cout << "P" << p.pid << "\t"
             << p.arrivalTime << "\t"
             << p.burstTime << "\t"
             << p.completionTime << "\t"
             << p.turnaroundTime << "\t"
             << p.waitingTime << "\t"
             << p.responseTime << endl;
    }

    // Display Gantt chart
    displayGanttChart(processes);

    // Display performance
    displayPerformance(processes);

    cout << "\n========================================\n";
    cout << "          SIMULATION COMPLETE\n";
    cout << "========================================\n";

    return 0;
}
