#include "performance.h"

using namespace std;

PerformanceMetrics calculatePerformanceMetrics(
    const vector<Process>& processes,
    const vector<GanttEntry>& gantt) {

    PerformanceMetrics metrics{0.0, 0};

    if (processes.empty() || gantt.empty()) {
        return metrics;
    }

    // Calculate total CPU busy time
    int totalBurstTime = 0;

    for (const auto& p : processes) {
        totalBurstTime += p.burstTime;
    }

    // Total elapsed simulation time
    int startTime = gantt.front().startTime;
    int endTime = gantt.back().endTime;

    int totalElapsedTime = endTime - startTime;

    if (totalElapsedTime > 0) {
        metrics.cpuUtilization =
            (static_cast<double>(totalBurstTime) /
             totalElapsedTime) * 100.0;
    }

    // Count context switches
    // A switch occurs when consecutive Gantt entries
    // belong to different processes.
    for (size_t i = 1; i < gantt.size(); i++) {

        if (gantt[i].pid != gantt[i - 1].pid) {
            metrics.contextSwitches++;
        }
    }

    return metrics;
}
