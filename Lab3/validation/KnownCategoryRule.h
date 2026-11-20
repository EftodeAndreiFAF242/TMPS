// Lab 3 - Open/Closed Principle (OCP): a rule that learns the categories from the departments of city hall

#pragma once

#include <map>
#include <string>

#include "Lab1/validation/Rule.h"

class Department;

// Categoria trebuie să aibă un departament
class KnownCategoryRule : public Rule {
public:
    explicit KnownCategoryRule(const std::map<std::string, const Department*>* departments);

    std::string check(const Report& report) override;

private:
    const std::map<std::string, const Department*>* departments;  // the category and its department
};
