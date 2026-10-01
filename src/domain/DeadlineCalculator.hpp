#pragma once

#include "domain/Report.hpp"
#include "domain/Types.hpp"

#include <chrono>
#include <optional>

namespace civicdesk {

/// Works out by when city hall has to answer a report.
///
/// SRP: the legal term is a rule of its own. If the law changes the number of days, or
/// starts counting working days, this is the only class that changes.
class DeadlineCalculator {
public:
    /// The general term for answering a petition: 30 calendar days.
    static constexpr std::chrono::days kDefaultTerm{30};

    explicit DeadlineCalculator(std::chrono::days term = kDefaultTerm) noexcept : term_{term} {}

    /// The last calendar day on which the report can still be answered in time.
    [[nodiscard]] std::chrono::sys_days dueDate(const Report& report) const noexcept;

    /// Calendar days left until the due date: 0 on the due date itself, negative once it
    /// has passed. Empty for a closed report, which has no deadline any more.
    [[nodiscard]] std::optional<int> daysLeft(const Report& report, TimePoint now) const noexcept;

private:
    std::chrono::days term_;
};

}  // namespace civicdesk
