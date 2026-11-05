#pragma once

#include <string>

// One problem reported by a citizen.
struct Report {
    int id;
    std::string category;     // for example "Pothole"
    std::string description;  // what the citizen wrote

    Report(std::string category, std::string description);
};
