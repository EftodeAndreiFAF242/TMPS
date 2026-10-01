#include "validation/ReportValidator.hpp"

#include <stdexcept>
#include <utility>

namespace civicdesk {

ReportValidator& ReportValidator::addRule(std::unique_ptr<IValidationRule> rule) {
    if (!rule) {
        throw std::invalid_argument{"A validation rule can't be null."};
    }
    rules_.push_back(std::move(rule));
    return *this;
}

ValidationResult ReportValidator::validate(const ReportDraft& draft) const {
    ValidationResult result;
    for (const auto& rule : rules_) {
        rule->check(draft, result);
    }
    return result;
}

}  // namespace civicdesk
