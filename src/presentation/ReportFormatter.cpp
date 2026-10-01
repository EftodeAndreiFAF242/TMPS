#include "presentation/ReportFormatter.hpp"

#include <iomanip>
#include <optional>
#include <sstream>

namespace civicdesk {

std::string formatDate(std::chrono::sys_days day) {
    const std::chrono::year_month_day date{day};
    std::ostringstream text;
    text << static_cast<int>(date.year()) << '-' << std::setfill('0') << std::setw(2)
         << static_cast<unsigned>(date.month()) << '-' << std::setw(2) << static_cast<unsigned>(date.day());
    return text.str();
}

std::string ReportFormatter::deadline(const Report& report, TimePoint now) const {
    const std::optional<int> daysLeft = deadlines_.daysLeft(report, now);
    if (!daysLeft) {
        return "closed";
    }

    std::ostringstream text;
    text << "due " << formatDate(deadlines_.dueDate(report)) << ", ";
    if (*daysLeft > 1) {
        text << *daysLeft << " days left";
    } else if (*daysLeft == 1) {
        text << "1 day left";
    } else if (*daysLeft == 0) {
        text << "last day";
    } else if (*daysLeft == -1) {
        text << "overdue by 1 day";
    } else {
        text << "overdue by " << -*daysLeft << " days";
    }
    return text.str();
}

std::string ReportFormatter::summary(const Report& report, TimePoint now) const {
    std::ostringstream line;
    line << std::left << std::setw(8) << report.id() << std::setw(14) << nameOf(report.category())
         << std::setw(13) << nameOf(report.status()) << std::setw(30) << deadline(report, now)
         << report.description();
    return line.str();
}

}  // namespace civicdesk
