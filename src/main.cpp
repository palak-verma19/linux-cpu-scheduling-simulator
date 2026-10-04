#include <iostream>
#include <vector>
#include <iomanip>
#include <string>
#include "../include/process.h"
#include "../include/comparison.h"

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

    for (size_t i = 0; i < gantt.size(); i++) {
        cout << "---------";
    }

    cout << "\n|";

    for (const auto& entry : gantt) {

        cout << "   P"
             << entry.pid
             << "   |";
    }

    cout << "\n ";

    for (size_t i = 0; i < gantt.size(); i++) {
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

        totalWaitingTime += p.waitingTime;
        totalTurnaroundTime += p.turnaroundTime;
        totalResponseTime += p.responseTime;
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


// Display algorithm comparison
void displayComparison(
    const vector<AlgorithmResult>& results) {

    cout << "\n\n";
    cout << "====================================================\n";
    cout << "        ALGORITHM PERFORMANCE COMPARISON\n";
    cout << "====================================================\n";

    cout << left
         << setw(18) << "Algorithm"
         << setw(15) << "Avg WT"
         << setw(15) << "Avg TAT"
         << setw(15) << "Avg RT"
         << endl;

    cout << "----------------------------------------------------\n";

    cout << fixed
         << setprecision(2);

    for (const auto& result : results) {

        cout << left
             << setw(18) << result.name
             << setw(15) << result.averageWaitingTime
             << setw(15) << result.averageTurnaroundTime
             << setw(15) << result.averageResponseTime
             << endl;
    }

    cout << "----------------------------------------------------\n";


    // Find best algorithms
    int bestWaiting = 0;
    int bestTurnaround = 0;
    int bestResponse = 0;

    for (size_t i = 1; i < results.size(); i++) {

        if (results[i].averageWaitingTime <
            results[bestWaiting].averageWaitingTime) {

            bestWaiting = i;
        }

        if (results[i].averageTurnaroundTime <
            results[bestTurnaround].averageTurnaroundTime) {

            bestTurnaround = i;
        }

        if (results[i].averageResponseTime <
            results[bestResponse].averageResponseTime) {

            bestResponse = i;
        }
    }


    cout << "\nBEST PERFORMANCE\n";
    cout << "----------------------------\n";

    cout << "Best Average Waiting Time    : "
         << results[bestWaiting].name
         << endl;

    cout << "Best Average Turnaround Time : "
         << results[bestTurnaround].name
         << endl;

    cout << "Best Average Response Time   : "
         << results[bestResponse].name
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


    int choice;

    cout << "\n========================================\n";
    cout << "       SELECT SCHEDULING ALGORITHM\n";
    cout << "========================================\n";

    cout << "1. FCFS\n";
    cout << "2. SJF\n";
    cout << "3. Priority Scheduling\n";
    cout << "4. Round Robin\n";
    cout << "5. Compare All Algorithms\n";

    cout << "\nEnter choice: ";
    cin >> choice;


    vector<GanttEntry> gantt;
    string algorithmName;


    if (choice == 1) {

        cout << "\nRunning FCFS Scheduling...\n";

        fcfs(processes, gantt);

        algorithmName = "FCFS";

        displayPerformance(processes);

        displayGanttChart(
            gantt,
            algorithmName);

        displayAveragePerformance(
            processes);
    }


    else if (choice == 2) {

        cout << "\nRunning SJF Scheduling...\n";

        sjf(processes, gantt);

        algorithmName = "SJF";

        displayPerformance(processes);

        displayGanttChart(
            gantt,
            algorithmName);

        displayAveragePerformance(
            processes);
    }


    else if (choice == 3) {

        cout << "\nRunning Priority Scheduling...\n";

        priorityScheduling(
            processes,
            gantt);

        algorithmName = "PRIORITY";

        displayPerformance(processes);

        displayGanttChart(
            gantt,
            algorithmName);

        displayAveragePerformance(
            processes);
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

        displayPerformance(processes);

        displayGanttChart(
            gantt,
            algorithmName);

        displayAveragePerformance(
            processes);
    }


    else if (choice == 5) {

        int quantum;

        cout << "\nEnter Time Quantum for Round Robin: ";
        cin >> quantum;

        if (quantum <= 0) {

            cout << "\nInvalid time quantum.\n";

            return 1;
        }

        cout << "\nRunning performance comparison...\n";

        vector<AlgorithmResult> results =
            compareAlgorithms(
                processes,
                quantum);

        displayComparison(results);
    }


    else {

        cout << "\nInvalid choice.\n";

        return 1;
    }


    cout << "\n========================================\n";
    cout << "          SIMULATION COMPLETE\n";
    cout << "========================================\n";


    return 0;
}
