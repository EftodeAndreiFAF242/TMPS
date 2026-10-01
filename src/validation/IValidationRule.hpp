#pragma once

#include "domain/Report.hpp"
#include "validation/ValidationResult.hpp"

namespace civicdesk {

/// One condition a report draft has to meet.
///
/// OCP: this interface is the extension point of validation. A new condition is a new
/// class that implements it. ReportValidator and the rules that already exist stay as
/// they are.
class IValidationRule {
public:
    virtual ~IValidationRule() = default;

    /// Adds an error to `result` if the draft breaks this rule, and does nothing otherwise.
    virtual void check(const ReportDraft& draft, ValidationResult& result) const = 0;
};

}  // namespace civicdesk
