// Lab 1 - Open/Closed Principle (OCP): a rule added without changing Validator

#pragma once

#include <string>

#include "Lab1/validation/Rule.h"

// The category has to be one the city hall works with.
class CategoryRule : public Rule {
public:
    std::string check(const Report& report) override;
};
