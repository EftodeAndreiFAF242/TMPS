// Lab 1 - Single Responsibility Principle (SRP): only keeps the reports

#pragma once

#include <vector>

#include "Lab1/reports/Report.h"

// Keeps the reports. For now they stay in memory, in a vector.
class ReportStorage {
public:
    // Saves a report, gives it the next free id and returns that id.
    int add(Report report);

    // Returns every saved report.
    std::vector<Report> all();

private:
    std::vector<Report> reports;
    int nextId = 1;
};
