// Lab 3 - Open/Closed Principle (OCP): a rule that learns the categories from the departments of city hall

#pragma once

#include <map>
#include <string>

#include "Lab1/validation/Rule.h"

class Department;

// The category of a report has to be one that a department of city hall takes care of. The rule
// looks at the departments city hall was given, so a new department brings its category with it,
// and no list of categories has to be changed.
class KnownCategoryRule : public Rule {
public:
    explicit KnownCategoryRule(const std::map<std::string, const Department*>* departments);

    std::string check(const Report& report) override;

private:
    const std::map<std::string, const Department*>* departments;  // the category and its department
};
