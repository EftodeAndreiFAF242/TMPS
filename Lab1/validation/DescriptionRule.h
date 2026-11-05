// Lab 1 - Open/Closed Principle (OCP): a rule added without changing Validator

#pragma once

#include <string>

#include "Lab1/validation/Rule.h"

// The description has to say something: at least 10 characters.
class DescriptionRule : public Rule {
public:
    std::string check(const Report& report) override;
};
