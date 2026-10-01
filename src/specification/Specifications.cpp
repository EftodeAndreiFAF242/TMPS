#include "specification/Specifications.hpp"

#include <algorithm>
#include <stdexcept>
#include <utility>

namespace civicdesk {

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

bool WithinRadius::isSatisfiedBy(const Report& report) const {
    return distanceMeters(center_, report.location()) <= radiusMeters_;
}

AllOf& AllOf::add(std::unique_ptr<IReportSpecification> part) {
    if (!part) {
        throw std::invalid_argument{"A specification can't be null."};
    }
    parts_.push_back(std::move(part));
    return *this;
}

bool AllOf::isSatisfiedBy(const Report& report) const {
    return std::ranges::all_of(parts_, [&report](const auto& part) { return part->isSatisfiedBy(report); });
}

}  // namespace civicdesk
