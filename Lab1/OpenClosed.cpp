#include "Lab1/OpenClosed.h"

#include "Lab1/SingleResponsibility.h"

using namespace std;

string CategoryRule::check(const Report& report) {
    if (report.category == "Pothole" || report.category == "Street light" || report.category == "Garbage") {
        return "";
    }
    return "\"" + report.category + "\" is not a known category.";
}

string DescriptionRule::check(const Report& report) {
    if (report.description.length() >= 10) {
        return "";
    }
    return "The description must have at least 10 characters.";
}

void Validator::addRule(Rule* rule) {
    rules.push_back(rule);
}

vector<string> Validator::validate(const Report& report) {
    vector<string> errors;
    // The loop does not know which rules it runs. That is why a new rule needs no change here.
    for (Rule* rule : rules) {
        string error = rule->check(report);
        if (error != "") {
            errors.push_back(error);
        }
    }
    return errors;
}
