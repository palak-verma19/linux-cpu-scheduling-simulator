#include <vector>
#include <queue>
#include <algorithm>
#include "../include/process.h"

using namespace std;

void roundRobin(vector<Process>& processes,
                int quantum,
                vector<GanttEntry>& gantt) {

    int n = processes.size();

    vector<int> remainingTime(n);
    vector<bool> added(n, false);

    queue<int> readyQueue;

    int completed = 0;
    int currentTime = 0;

    for (int i = 0; i < n; i++) {

        remainingTime[i] =
            processes[i].burstTime;

        processes[i].responseTime = -1;
    }

    while (completed < n) {

        // Add arrived processes
        for (int i = 0; i < n; i++) {

            if (!added[i] &&
                processes[i].arrivalTime <= currentTime) {

                readyQueue.push(i);
                added[i] = true;
            }
        }

        // CPU idle
        if (readyQueue.empty()) {

            currentTime++;
            continue;
        }

        int index =
            readyQueue.front();

        readyQueue.pop();

        // First CPU response
        if (processes[index].responseTime == -1) {

            processes[index].responseTime =
                currentTime -
                processes[index].arrivalTime;
        }

        int startTime = currentTime;

        int executionTime =
            min(quantum, remainingTime[index]);

        currentTime += executionTime;

        remainingTime[index] -= executionTime;

        // Record every Round Robin time slice
        gantt.push_back({
            processes[index].pid,
            startTime,
            currentTime
        });

        // Add processes that arrived during execution
        for (int i = 0; i < n; i++) {

            if (!added[i] &&
                processes[i].arrivalTime <= currentTime) {

                readyQueue.push(i);
                added[i] = true;
            }
        }

        if (remainingTime[index] == 0) {

            processes[index].completionTime =
                currentTime;

            processes[index].turnaroundTime =
                processes[index].completionTime -
                processes[index].arrivalTime;

            processes[index].waitingTime =
                processes[index].turnaroundTime -
                processes[index].burstTime;

            completed++;
        }
        else {

            readyQueue.push(index);
        }
    }
}
