#ifndef PERFORMANCE_H
#define PERFORMANCE_H

#include <vector>
#include "process.h"

struct PerformanceMetrics {
    double cpuUtilization;
    int contextSwitches;
};

PerformanceMetrics calculatePerformanceMetrics(
    const std::vector<Process>& processes,
    const std::vector<GanttEntry>& gantt);

#endif
