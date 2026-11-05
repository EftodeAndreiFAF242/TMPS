// Lab 1 - Single Responsibility Principle (SRP): only holds the data of a report

#pragma once

#include <string>

// One problem reported by a citizen.
struct Report {
    int id;
    std::string category;     // for example "Pothole"
    std::string description;  // what the citizen wrote

    Report(std::string category, std::string description);
};
