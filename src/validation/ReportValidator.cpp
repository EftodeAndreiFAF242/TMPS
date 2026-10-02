// ReportValidator.cpp
// Implementation of the validator: it keeps the rules it is given and runs all of them.

#include "validation/ReportValidator.hpp"

#include <stdexcept>
#include <utility>

using namespace std;

namespace civicdesk {

ReportValidator& ReportValidator::addRule(unique_ptr<IValidationRule> rule) {
    // A null rule would crash later, inside validate(). Refusing it here points at the
    // real mistake.
    if (!rule) {
        throw invalid_argument{"A validation rule can't be null."};
    }
    // From here on the validator owns the rule.
    rules_.push_back(move(rule));
    // Returning the validator allows addRule(...).addRule(...) in one statement.
    return *this;
}

ValidationResult ReportValidator::validate(const ReportDraft& draft) const {
    ValidationResult result;
    // OCP: the loop never asks which rule it is running. Any class that implements
    // IValidationRule works here, including the ones written after this file.
    for (const auto& rule : rules_) {
        rule->check(draft, result);
    }
    return result;
}

}  // namespace civicdesk
