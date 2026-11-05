#include "Lab1/validation/DescriptionRule.h"

#include "Lab1/reports/Report.h"

using namespace std;

string DescriptionRule::check(const Report& report) {
    if (report.description.length() >= 10) {
        return "";
    }
    return "The description must have at least 10 characters.";
}
