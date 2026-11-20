// Lab 3 - Adapter: the Target, the dates city hall needs, in the form the project wants them

#pragma once

#include <string>

// What the project needs from a calendar: the date that is a number of days from today, written
// the way people here read it, for example 22.11.2026.
class Calendar {
public:
    virtual ~Calendar() {}
    virtual std::string dateIn(int days) const = 0;
};
