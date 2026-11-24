// "Each piece of software should be open for extension and closed for modification."
// Lab 3 - Open/Closed Principle (OCP): a rule that learns the categories from the departments of city hall

#include "Lab3/validation/KnownCategoryRule.h"

#include "Lab1/reports/Report.h"

using namespace std;

KnownCategoryRule::KnownCategoryRule(const map<string, const Department*>* departments) {
    this->departments = departments;
}

string KnownCategoryRule::check(const Report& report) {
    if (departments->count(report.category) == 0) {
        return "\"" + report.category + "\" is not a known category.";
    }
    return "";
}
