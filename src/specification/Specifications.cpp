// Specifications.cpp
// Implementation of the search conditions. Each one answers a single yes-or-no question
// about a report.

#include "specification/Specifications.hpp"

#include <algorithm>
#include <stdexcept>
#include <utility>

using namespace std;

namespace civicdesk {

// The parameter has no name because every report matches, whatever it holds.
bool AnyReport::isSatisfiedBy(const Report& /*report*/) const {
    return true;
}

bool HasCategory::isSatisfiedBy(const Report& report) const {
    return report.category() == category_;
}

bool HasStatus::isSatisfiedBy(const Report& report) const {
    return report.status() == status_;
}

bool IsOpen::isSatisfiedBy(const Report& report) const {
    return report.isOpen();
}

// A report exactly on the edge of the circle still counts as inside.
bool WithinRadius::isSatisfiedBy(const Report& report) const {
    return distanceMeters(center_, report.location()) <= radiusMeters_;
}

AllOf& AllOf::add(unique_ptr<IReportSpecification> part) {
    if (!part) {
        throw invalid_argument{"A specification can't be null."};
    }
    // From here on AllOf owns the condition.
    parts_.push_back(move(part));
    return *this;
}

// all_of stops at the first part that says no. With no parts it returns true, which is
// why an empty AllOf matches every report.
bool AllOf::isSatisfiedBy(const Report& report) const {
    return ranges::all_of(parts_, [&report](const auto& part) { return part->isSatisfiedBy(report); });
}

}  // namespace civicdesk
