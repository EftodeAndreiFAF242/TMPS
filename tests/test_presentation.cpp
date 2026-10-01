#include "presentation/ReportFormatter.hpp"
#include "support/Fakes.hpp"

#include <doctest/doctest.h>

#include <chrono>
#include <string>

using namespace civicdesk;
using namespace civicdesk::testing;

TEST_SUITE("ReportFormatter") {
    TEST_CASE("formatDate pads the month and the day") {
        CHECK(formatDate(std::chrono::floor<std::chrono::days>(at(2026, 3, 7))) == "2026-03-07");
    }

    TEST_CASE("the deadline is worded by how many days are left") {
        const ReportFormatter formatter;
        const Report report = makeReport();  // created on 2026-10-01, due on 2026-10-31

        CHECK(formatter.deadline(report, at(2026, 10, 1)) == "due 2026-10-31, 30 days left");
        CHECK(formatter.deadline(report, at(2026, 10, 30)) == "due 2026-10-31, 1 day left");
        CHECK(formatter.deadline(report, at(2026, 10, 31)) == "due 2026-10-31, last day");
        CHECK(formatter.deadline(report, at(2026, 11, 1)) == "due 2026-10-31, overdue by 1 day");
        CHECK(formatter.deadline(report, at(2026, 11, 5)) == "due 2026-10-31, overdue by 5 days");
    }

    TEST_CASE("a closed report shows no deadline") {
        const ReportFormatter formatter;
        Report report = makeReport();
        report.transitionTo(Status::Rejected);

        CHECK(formatter.deadline(report, at(2026, 10, 2)) == "closed");
    }

    TEST_CASE("the summary line holds the id, category, status, deadline and description") {
        const ReportFormatter formatter;
        const Report report{"R-0001", Category::Garbage, "Bags on the pavement", kChisinau, at(2026, 10, 1)};

        const std::string line = formatter.summary(report, at(2026, 10, 1));

        CHECK(line == "R-0001  Garbage       New          due 2026-10-31, 30 days left  Bags on the pavement");
    }
}
