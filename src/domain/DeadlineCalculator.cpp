#include "domain/DeadlineCalculator.hpp"

namespace civicdesk {

std::chrono::sys_days DeadlineCalculator::dueDate(const Report& report) const noexcept {
    // The term runs in whole calendar days, so the hour of the report doesn't matter.
    return std::chrono::floor<std::chrono::days>(report.createdAt()) + term_;
}

std::optional<int> DeadlineCalculator::daysLeft(const Report& report, TimePoint now) const noexcept {
    if (!report.isOpen()) {
        return std::nullopt;
    }
    const std::chrono::sys_days today = std::chrono::floor<std::chrono::days>(now);
    return static_cast<int>((dueDate(report) - today).count());
}

}  // namespace civicdesk
