#include <vector>
#include <algorithm>
#include "../include/process.h"

using namespace std;

void fcfs(vector<Process>& processes,
          vector<GanttEntry>& gantt) {

    sort(processes.begin(), processes.end(),
         [](const Process& a, const Process& b) {
             return a.arrivalTime < b.arrivalTime;
         });

    int currentTime = 0;

    for (auto& p : processes) {

        if (currentTime < p.arrivalTime) {
            currentTime = p.arrivalTime;
        }

        int startTime = currentTime;

        p.responseTime =
            currentTime - p.arrivalTime;

        currentTime += p.burstTime;

        gantt.push_back({
            p.pid,
            startTime,
            currentTime
        });

        p.completionTime = currentTime;

        p.turnaroundTime =
            p.completionTime - p.arrivalTime;

        p.waitingTime =
            p.turnaroundTime - p.burstTime;
    }
}
