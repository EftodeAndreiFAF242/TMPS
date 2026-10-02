// DeadlineCalculator.cpp
// Implementation of the answer deadline: the due date of a report and the days left until it.

#include "domain/DeadlineCalculator.hpp"

using namespace std;

namespace civicdesk {

chrono::sys_days DeadlineCalculator::dueDate(const Report& report) const noexcept {
    // floor<days> cuts the hour off. The term runs in whole calendar days, so a report sent
    // at 23:00 is due on the same day as one sent at 08:00.
    return chrono::floor<chrono::days>(report.createdAt()) + term_;
}

optional<int> DeadlineCalculator::daysLeft(const Report& report, TimePoint now) const noexcept {
    // A resolved or rejected report has no deadline any more.
    if (!report.isOpen()) {
        return nullopt;
    }
    const chrono::sys_days today = chrono::floor<chrono::days>(now);
    // Positive before the due date, 0 on the due date, negative after it.
    return static_cast<int>((dueDate(report) - today).count());
}

}  // namespace civicdesk
