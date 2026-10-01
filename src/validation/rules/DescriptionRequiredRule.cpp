#include "validation/rules/DescriptionRequiredRule.hpp"

#include "support/Text.hpp"

#include <string>
#include <utility>

namespace civicdesk {

void DescriptionRequiredRule::check(const ReportDraft& draft, ValidationResult& result) const {
    if (draft.category == category_ && isBlank(draft.description)) {
        std::string message{"A report in the category \""};
        message += nameOf(category_);
        message += "\" needs a description.";
        result.addError(std::move(message));
    }
}

}  // namespace civicdesk
