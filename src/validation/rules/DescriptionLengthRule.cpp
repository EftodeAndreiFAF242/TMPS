#include "validation/rules/DescriptionLengthRule.hpp"

#include <string>

namespace civicdesk {

void DescriptionLengthRule::check(const ReportDraft& draft, ValidationResult& result) const {
    if (draft.description.size() > maxLength_) {
        result.addError("The description can have at most " + std::to_string(maxLength_) + " characters.");
    }
}

}  // namespace civicdesk
