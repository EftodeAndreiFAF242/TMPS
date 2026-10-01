#pragma once

#include "domain/Category.hpp"
#include "validation/IValidationRule.hpp"

namespace civicdesk {

/// Reports of one given category have to come with a description.
/// "Other" is the typical case: without a description nobody knows what the problem is.
class DescriptionRequiredRule final : public IValidationRule {
public:
    explicit DescriptionRequiredRule(Category category) noexcept : category_{category} {}

    void check(const ReportDraft& draft, ValidationResult& result) const override;

private:
    Category category_;
};

}  // namespace civicdesk
