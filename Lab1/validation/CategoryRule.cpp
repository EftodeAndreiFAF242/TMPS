// Lab 1 - Open/Closed Principle (OCP): a rule added without changing Validator

#include "Lab1/validation/CategoryRule.h"

#include "Lab1/reports/Report.h"

using namespace std;

string CategoryRule::check(const Report& report) {
    if (report.category == "Pothole" || report.category == "Street light" || report.category == "Garbage") {
        return "";
    }
    return "\"" + report.category + "\" is not a known category.";
}
