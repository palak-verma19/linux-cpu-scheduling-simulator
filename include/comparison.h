#ifndef COMPARISON_H
#define COMPARISON_H

#include <vector>
#include <string>
#include "process.h"

struct AlgorithmResult {
    std::string name;
    double averageWaitingTime;
    double averageTurnaroundTime;
    double averageResponseTime;
};

std::vector<AlgorithmResult> compareAlgorithms(
    const std::vector<Process>& processes,
    int quantum);

#endif
