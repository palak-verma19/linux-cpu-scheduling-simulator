#include <vector>
#include "../include/process.h"

using namespace std;

void priorityScheduling(vector<Process>& processes,
                         vector<GanttEntry>& gantt) {

    int n = processes.size();
    int completed = 0;
    int currentTime = 0;

    vector<bool> finished(n, false);

    while (completed < n) {

        int selectedIndex = -1;
        int highestPriority = 999999;

        for (int i = 0; i < n; i++) {

            if (!finished[i] &&
                processes[i].arrivalTime <= currentTime &&
                processes[i].priority < highestPriority) {

                highestPriority =
                    processes[i].priority;

                selectedIndex = i;
            }
        }

        if (selectedIndex == -1) {
            currentTime++;
            continue;
        }

        Process& p =
            processes[selectedIndex];

        int startTime = currentTime;

        p.responseTime =
            currentTime - p.arrivalTime;

        currentTime += p.burstTime;

        gantt.push_back({
            p.pid,
            startTime,
            currentTime
        });

        p.completionTime =
            currentTime;

        p.turnaroundTime =
            p.completionTime - p.arrivalTime;

        p.waitingTime =
            p.turnaroundTime - p.burstTime;

        finished[selectedIndex] = true;

        completed++;
    }
}
