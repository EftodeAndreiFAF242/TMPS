// Lab 1 - Open/Closed Principle (OCP): runs any rules it is given, and its code never changes

#pragma once

#include <string>
#include <vector>

struct Report;
class Rule;

// Checks a report against every rule it was given.
class Validator {
public:
    void addRule(Rule* rule);

    // Returns the error messages. An empty list means the report is valid.
    std::vector<std::string> validate(const Report& report);

private:
    std::vector<Rule*> rules;
};
