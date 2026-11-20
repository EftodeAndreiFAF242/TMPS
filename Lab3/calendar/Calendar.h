// Lab 3 - Adapter: the Target, the dates city hall needs, in the form the project wants them

#pragma once

#include <string>

// Dates the project needs, like 22.11.2026
class Calendar {
public:
    virtual ~Calendar() {}
    virtual std::string dateIn(int days) const = 0;
};
