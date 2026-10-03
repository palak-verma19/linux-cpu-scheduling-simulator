#include <iostream>
#include <vector>
#include <iomanip>
#include "../include/process.h"

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


// Display process performance
void displayPerformance(
    const vector<Process>& processes) {

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
             << setw(8)
             << ("P" + to_string(p.pid))

             << setw(8)
             << p.arrivalTime

             << setw(8)
             << p.burstTime

             << setw(8)
             << p.completionTime

             << setw(8)
             << p.turnaroundTime

             << setw(8)
             << p.waitingTime

             << setw(8)
             << p.responseTime

             << endl;
    }
}


// Display Gantt Chart
void displayGanttChart(
    const vector<GanttEntry>& gantt,
    const string& algorithm) {

    cout << "\n\n"
         << algorithm
         << " GANTT CHART\n\n";

    if (gantt.empty()) {
        cout << "No execution data available.\n";
        return;
    }

    cout << " ";

    for (const auto& entry : gantt) {
        cout << "---------";
    }

    cout << "\n|";

    for (const auto& entry : gantt) {

        cout << "   P"
             << entry.pid
             << "   |";
    }

    cout << "\n ";

    for (const auto& entry : gantt) {
        cout << "---------";
    }

    cout << "\n";

    for (const auto& entry : gantt) {
        cout << entry.startTime << "\t";
    }

    cout << gantt.back().endTime << "\n";
}


// Display average performance
void displayAveragePerformance(
    const vector<Process>& processes) {

    double totalWaitingTime = 0;
    double totalTurnaroundTime = 0;
    double totalResponseTime = 0;

    for (const auto& p : processes) {

        totalWaitingTime +=
            p.waitingTime;

        totalTurnaroundTime +=
            p.turnaroundTime;

        totalResponseTime +=
            p.responseTime;
    }

    int n = processes.size();

    cout << "\nPERFORMANCE ANALYSIS\n";
    cout << "----------------------------\n";

    cout << fixed
         << setprecision(2);

    cout << "Average Waiting Time    : "
         << totalWaitingTime / n
         << endl;

    cout << "Average Turnaround Time : "
         << totalTurnaroundTime / n
         << endl;

    cout << "Average Response Time   : "
         << totalResponseTime / n
         << endl;
}


// Main function
int main() {

    cout << "========================================\n";
    cout << "   LINUX CPU SCHEDULING SIMULATOR\n";
    cout << "========================================\n";


    int n;

    cout << "\nEnter number of processes: ";
    cin >> n;

    if (n <= 0) {

        cout << "\nInvalid number of processes.\n";

        return 1;
    }


    vector<Process> processes(n);


    // Input process information
    for (int i = 0; i < n; i++) {

        processes[i].pid = i + 1;

        cout << "\nProcess P"
             << processes[i].pid
             << endl;

        cout << "Arrival Time: ";
        cin >> processes[i].arrivalTime;

        cout << "Burst Time: ";
        cin >> processes[i].burstTime;

        cout << "Priority: ";
        cin >> processes[i].priority;

        if (processes[i].arrivalTime < 0 ||
            processes[i].burstTime <= 0) {

            cout << "\nInvalid process data.\n";

            return 1;
        }
    }


    vector<GanttEntry> gantt;


    // Algorithm selection
    int choice;

    cout << "\n========================================\n";
    cout << "       SELECT SCHEDULING ALGORITHM\n";
    cout << "========================================\n";

    cout << "1. FCFS\n";
    cout << "2. SJF\n";
    cout << "3. Priority Scheduling\n";
    cout << "4. Round Robin\n";

    cout << "\nEnter choice: ";
    cin >> choice;


    string algorithmName;


    if (choice == 1) {

        cout << "\nRunning FCFS Scheduling...\n";

        fcfs(processes, gantt);

        algorithmName = "FCFS";
    }


    else if (choice == 2) {

        cout << "\nRunning SJF Scheduling...\n";

        sjf(processes, gantt);

        algorithmName = "SJF";
    }


    else if (choice == 3) {

        cout << "\nRunning Priority Scheduling...\n";

        priorityScheduling(
            processes,
            gantt);

        algorithmName = "PRIORITY";
    }


    else if (choice == 4) {

        int quantum;

        cout << "\nEnter Time Quantum: ";
        cin >> quantum;

        if (quantum <= 0) {

            cout << "\nInvalid time quantum.\n";

            return 1;
        }

        cout << "\nRunning Round Robin Scheduling...\n";

        roundRobin(
            processes,
            quantum,
            gantt);

        algorithmName = "ROUND ROBIN";
    }


    else {

        cout << "\nInvalid choice.\n";

        return 1;
    }


    // Display results
    displayPerformance(processes);

    displayGanttChart(
        gantt,
        algorithmName);

    displayAveragePerformance(
        processes);


    cout << "\n========================================\n";
    cout << "          SIMULATION COMPLETE\n";
    cout << "========================================\n";


    return 0;
}
