// DescriptionLengthRule.cpp
// Implementation of the rule that limits the length of the description.

#include "validation/rules/DescriptionLengthRule.hpp"

#include <string>

using namespace std;

namespace civicdesk {

void DescriptionLengthRule::check(const ReportDraft& draft, ValidationResult& result) const {
    // A description exactly at the limit is still accepted.
    if (draft.description.size() > maxLength_) {
        result.addError("The description can have at most " + to_string(maxLength_) + " characters.");
    }
}

}  // namespace civicdesk
