#include <iostream>
#include <vector>
#include "../include/process.h"

using namespace std;

void sjf(vector<Process>& processes) {

    int n = processes.size();
    int completed = 0;
    int currentTime = 0;

    vector<bool> finished(n, false);

    while (completed < n) {

        int shortestIndex = -1;
        int shortestBurst = 999999;

        // Find the shortest job among arrived processes
        for (int i = 0; i < n; i++) {

            if (!finished[i] &&
                processes[i].arrivalTime <= currentTime &&
                processes[i].burstTime < shortestBurst) {

                shortestBurst = processes[i].burstTime;
                shortestIndex = i;
            }
        }

        // If no process has arrived yet
        if (shortestIndex == -1) {

            currentTime++;

            continue;
        }

        Process& p = processes[shortestIndex];

        // Response Time
        p.responseTime = currentTime - p.arrivalTime;

        // Execute the process
        currentTime += p.burstTime;

        // Completion Time
        p.completionTime = currentTime;

        // Turnaround Time
        p.turnaroundTime =
            p.completionTime - p.arrivalTime;

        // Waiting Time
        p.waitingTime =
            p.turnaroundTime - p.burstTime;

        finished[shortestIndex] = true;

        completed++;
    }
}
