#include <iostream>
#include <vector>
#include <algorithm>
#include "../include/process.h"

using namespace std;

void fcfs(vector<Process>& processes) {

    // Sort processes according to arrival time
    sort(processes.begin(), processes.end(),
         [](const Process& a, const Process& b) {
             return a.arrivalTime < b.arrivalTime;
         });

    int currentTime = 0;

    for (auto& p : processes) {

        // CPU remains idle if process has not arrived
        if (currentTime < p.arrivalTime) {
            currentTime = p.arrivalTime;
        }

        // Response Time
        p.responseTime = currentTime - p.arrivalTime;

        // Execute process
        currentTime += p.burstTime;

        // Completion Time
        p.completionTime = currentTime;

        // Turnaround Time
        p.turnaroundTime =
            p.completionTime - p.arrivalTime;

        // Waiting Time
        p.waitingTime =
            p.turnaroundTime - p.burstTime;
    }
}
