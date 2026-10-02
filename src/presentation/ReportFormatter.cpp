// ReportFormatter.cpp
// Implementation of the formatter: the wording of the deadline and the layout of the line
// printed for each report.

#include "presentation/ReportFormatter.hpp"

#include <iomanip>
#include <optional>
#include <sstream>

using namespace std;

namespace civicdesk {

string formatDate(chrono::sys_days day) {
    // year_month_day splits the day into the three numbers of a calendar date.
    const chrono::year_month_day date{day};
    ostringstream text;
    // setw(2) with setfill('0') writes the month and the day with two digits: 3 becomes 03.
    text << static_cast<int>(date.year()) << '-' << setfill('0') << setw(2)
         << static_cast<unsigned>(date.month()) << '-' << setw(2) << static_cast<unsigned>(date.day());
    return text.str();
}

string ReportFormatter::deadline(const Report& report, TimePoint now) const {
    // The calculation belongs to DeadlineCalculator. The formatter only puts it into words.
    const optional<int> daysLeft = deadlines_.daysLeft(report, now);
    if (!daysLeft) {
        return "closed";
    }

    ostringstream text;
    text << "due " << formatDate(deadlines_.dueDate(report)) << ", ";
    // Singular and plural are written out, so the text never says "1 days".
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

string ReportFormatter::summary(const Report& report, TimePoint now) const {
    ostringstream line;
    // left with setw gives every column a fixed width, so the lines form a table.
    line << left << setw(8) << report.id() << setw(14) << nameOf(report.category())
         << setw(13) << nameOf(report.status()) << setw(30) << deadline(report, now)
         << report.description();
    return line.str();
}

}  // namespace civicdesk
