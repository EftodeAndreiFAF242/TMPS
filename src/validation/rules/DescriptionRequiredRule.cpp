// DescriptionRequiredRule.cpp
// Implementation of the rule that asks for a description in one given category.

#include "validation/rules/DescriptionRequiredRule.hpp"

#include "support/Text.hpp"

#include <string>
#include <utility>

using namespace std;

namespace civicdesk {

void DescriptionRequiredRule::check(const ReportDraft& draft, ValidationResult& result) const {
    // The rule only looks at its own category. isBlank also catches a description made of
    // spaces, which says as little as an empty one.
    if (draft.category == category_ && isBlank(draft.description)) {
        string message{"A report in the category \""};
        message += nameOf(category_);
        message += "\" needs a description.";
        result.addError(move(message));
    }
}

}  // namespace civicdesk
