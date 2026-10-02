// DescriptionLengthRule.hpp
// Validation rule: the description can't be longer than a given limit.

#pragma once

#include "validation/IValidationRule.hpp"

#include <cstddef>

using namespace std;

namespace civicdesk {

/// The description can't be longer than a fixed number of characters.
class DescriptionLengthRule final : public IValidationRule {
public:
    explicit DescriptionLengthRule(size_t maxLength) noexcept : maxLength_{maxLength} {}

    void check(const ReportDraft& draft, ValidationResult& result) const override;

private:
    size_t maxLength_;
};

}  // namespace civicdesk
