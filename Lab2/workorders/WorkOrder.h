#pragma once

#include <string>

// The task city hall gives to a department for one report.
struct WorkOrder {
    int reportId = 0;
    std::string problem;
    std::string address;
    std::string priority = "Normal";
    int deadlineDays = 7;
    std::string note;
};
