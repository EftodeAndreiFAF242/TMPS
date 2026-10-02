// ServiceAreaRule.cpp
// Implementation of the rule that keeps reports inside the service area.

#include "validation/rules/ServiceAreaRule.hpp"

namespace civicdesk {

void ServiceAreaRule::check(const ReportDraft& draft, ValidationResult& result) const {
    // A NaN coordinate fails every comparison in contains(), so it is refused here as well.
    if (!area_.contains(draft.location)) {
        result.addError("The location is outside the service area.");
    }
}

}  // namespace civicdesk
