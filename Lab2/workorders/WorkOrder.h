// Lab 2 - Builder: the product

#pragma once

#include <string>

// The task city hall gives to a department for one report.
// WorkOrderBuilder gives the priority and the deadline their default values from AppConfig.
struct WorkOrder {
    int reportId = 0;
    std::string problem;
    std::string address;
    std::string priority;
    int deadlineDays = 0;
    std::string note;
};
