// Lab 1 - Open/Closed Principle (OCP): runs any rules it is given, and its code never changes

#include "Lab1/validation/Validator.h"

#include "Lab1/validation/Rule.h"

using namespace std;

void Validator::addRule(Rule* rule) {
    rules.push_back(rule);
}

vector<string> Validator::validate(const Report& report) {
    vector<string> errors;
    // The loop does not know which rules it runs, so a new rule needs no change here.
    for (Rule* rule : rules) {
        string error = rule->check(report);
        if (error != "") {
            errors.push_back(error);
        }
    }
    return errors;
}
