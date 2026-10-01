#pragma once

#include "validation/IValidationRule.hpp"

#include <cstddef>

namespace civicdesk {

/// The description can't be longer than a fixed number of characters.
class DescriptionLengthRule final : public IValidationRule {
public:
    explicit DescriptionLengthRule(std::size_t maxLength) noexcept : maxLength_{maxLength} {}

    void check(const ReportDraft& draft, ValidationResult& result) const override;

private:
    std::size_t maxLength_;
};

}  // namespace civicdesk
