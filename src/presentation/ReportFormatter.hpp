#pragma once

#include "domain/DeadlineCalculator.hpp"
#include "domain/Report.hpp"
#include "domain/Types.hpp"

#include <chrono>
#include <string>

namespace civicdesk {

/// A calendar day written as YYYY-MM-DD.
[[nodiscard]] std::string formatDate(std::chrono::sys_days day);

/// Turns a report into text for a person to read.
///
/// SRP: how a report looks on screen changes for other reasons than what a report is, so
/// the wording and the layout live here and not in Report.
class ReportFormatter {
public:
    explicit ReportFormatter(DeadlineCalculator deadlines = DeadlineCalculator{}) noexcept : deadlines_{deadlines} {}

    /// One line with the id, the category, the status, the deadline and the description.
    [[nodiscard]] std::string summary(const Report& report, TimePoint now) const;

    /// The deadline in words: "due 2026-10-31, 12 days left", or "closed" for a closed report.
    [[nodiscard]] std::string deadline(const Report& report, TimePoint now) const;

private:
    DeadlineCalculator deadlines_;
};

}  // namespace civicdesk
