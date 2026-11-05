// Lab 1 - Open/Closed Principle (OCP): the interface every new rule plugs into

#pragma once

#include <string>

struct Report;

// One check a report has to pass. Every validation rule inherits from this class.
class Rule {
public:
    virtual ~Rule() {}

    // Returns an empty text if the report is fine, or the error message if it is not.
    virtual std::string check(const Report& report) = 0;
};
