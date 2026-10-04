#include <iostream>
#include <vector>
#include <cmath>

#include "../include/process.h"
#include "../include/performance.h"

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


bool checkEqual(int actual, int expected) {
    return actual == expected;
}


bool checkDouble(double actual, double expected) {
    return fabs(actual - expected) < 0.01;
}


// Test FCFS
bool testFCFS() {

    vector<Process> processes = {
        {1, 0, 5, 2, 0, 0, 0, 0},
        {2, 1, 3, 1, 0, 0, 0, 0},
        {3, 2, 8, 3, 0, 0, 0, 0},
        {4, 3, 2, 2, 0, 0, 0, 0}
    };

    vector<GanttEntry> gantt;

    fcfs(processes, gantt);

    return
        checkEqual(processes[0].completionTime, 5) &&
        checkEqual(processes[1].completionTime, 8) &&
        checkEqual(processes[2].completionTime, 16) &&
        checkEqual(processes[3].completionTime, 18);
}


// Test SJF
bool testSJF() {

    vector<Process> processes = {
        {1, 0, 5, 2, 0, 0, 0, 0},
        {2, 1, 3, 1, 0, 0, 0, 0},
        {3, 2, 8, 3, 0, 0, 0, 0},
        {4, 3, 2, 2, 0, 0, 0, 0}
    };

    vector<GanttEntry> gantt;

    sjf(processes, gantt);

    return
        checkEqual(processes[0].completionTime, 5) &&
        checkEqual(processes[3].completionTime, 7) &&
        checkEqual(processes[1].completionTime, 10) &&
        checkEqual(processes[2].completionTime, 18);
}


// Test Priority Scheduling
bool testPriority() {

    vector<Process> processes = {
        {1, 0, 5, 2, 0, 0, 0, 0},
        {2, 1, 3, 1, 0, 0, 0, 0},
        {3, 2, 8, 3, 0, 0, 0, 0},
        {4, 3, 2, 2, 0, 0, 0, 0}
    };

    vector<GanttEntry> gantt;

    priorityScheduling(processes, gantt);

    return
        checkEqual(processes[0].completionTime, 5) &&
        checkEqual(processes[1].completionTime, 8) &&
        checkEqual(processes[3].completionTime, 10) &&
        checkEqual(processes[2].completionTime, 18);
}


// Test Round Robin
bool testRoundRobin() {

    vector<Process> processes = {
        {1, 0, 5, 2, 0, 0, 0, 0},
        {2, 1, 3, 1, 0, 0, 0, 0},
        {3, 2, 8, 3, 0, 0, 0, 0},
        {4, 3, 2, 2, 0, 0, 0, 0}
    };

    vector<GanttEntry> gantt;

    roundRobin(processes, 2, gantt);

    return
        checkEqual(processes[0].completionTime, 14) &&
        checkEqual(processes[1].completionTime, 11) &&
        checkEqual(processes[2].completionTime, 18) &&
        checkEqual(processes[3].completionTime, 10);
}


// Test performance metrics
bool testPerformanceMetrics() {

    vector<Process> processes = {
        {1, 0, 5, 2, 5, 5, 0, 0},
        {2, 1, 3, 1, 8, 7, 4, 4},
        {3, 2, 8, 3, 16, 14, 6, 6},
        {4, 3, 2, 2, 18, 15, 13, 13}
    };

    vector<GanttEntry> gantt = {
        {1, 0, 5},
        {2, 5, 8},
        {3, 8, 16},
        {4, 16, 18}
    };

    PerformanceMetrics metrics =
        calculatePerformanceMetrics(
            processes,
            gantt);

    return
        checkDouble(metrics.cpuUtilization, 100.0) &&
        checkEqual(metrics.contextSwitches, 3);
}


// Print test result
void printResult(
    const string& name,
    bool passed) {

    if (passed) {
        cout << "[PASS] " << name << endl;
    }
    else {
        cout << "[FAIL] " << name << endl;
    }
}


// Main test runner
int main() {

    cout << "\n";
    cout << "========================================\n";
    cout << "       CPU SCHEDULING TEST SUITE\n";
    cout << "========================================\n\n";


    bool allPassed = true;


    bool result;


    result = testFCFS();
    printResult("FCFS", result);
    allPassed = allPassed && result;


    result = testSJF();
    printResult("SJF", result);
    allPassed = allPassed && result;


    result = testPriority();
    printResult("Priority Scheduling", result);
    allPassed = allPassed && result;


    result = testRoundRobin();
    printResult("Round Robin", result);
    allPassed = allPassed && result;


    result = testPerformanceMetrics();
    printResult("Performance Metrics", result);
    allPassed = allPassed && result;


    cout << "\n";

    if (allPassed) {

        cout << "All tests passed.\n";
        return 0;
    }

    cout << "Some tests failed.\n";
    return 1;
}
