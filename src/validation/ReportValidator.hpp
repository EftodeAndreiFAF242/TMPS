#pragma once

#include "domain/Report.hpp"
#include "validation/IValidationRule.hpp"
#include "validation/ValidationResult.hpp"

#include <cstddef>
#include <memory>
#include <vector>

namespace civicdesk {

/// Checks a report draft against a set of rules.
///
/// SRP: its only job is to decide whether a draft is acceptable.
/// OCP: it is closed for modification, because it knows nothing about any concrete rule,
/// and open for extension, because any number of rules can be plugged in from outside.
class ReportValidator {
public:
    /// Plugs in one more rule. Returns the validator, so calls can be chained.
    ReportValidator& addRule(std::unique_ptr<IValidationRule> rule);

    /// Runs every rule, so the citizen sees all the problems at once and not one at a time.
    [[nodiscard]] ValidationResult validate(const ReportDraft& draft) const;

    [[nodiscard]] std::size_t ruleCount() const noexcept { return rules_.size(); }

private:
    std::vector<std::unique_ptr<IValidationRule>> rules_;
};

}  // namespace civicdesk
