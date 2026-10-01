#include "domain/DeadlineCalculator.hpp"
#include "domain/GeoPoint.hpp"
#include "domain/Report.hpp"
#include "domain/Status.hpp"
#include "support/Fakes.hpp"

#include <doctest/doctest.h>

#include <chrono>
#include <limits>

using namespace civicdesk;
using namespace civicdesk::testing;

TEST_SUITE("Status") {
    TEST_CASE("only resolved and rejected reports are closed") {
        CHECK_FALSE(isClosed(Status::New));
        CHECK_FALSE(isClosed(Status::InProgress));
        CHECK(isClosed(Status::Resolved));
        CHECK(isClosed(Status::Rejected));
    }

    TEST_CASE("an open report can move forward") {
        CHECK(canTransition(Status::New, Status::InProgress));
        CHECK(canTransition(Status::New, Status::Resolved));
        CHECK(canTransition(Status::New, Status::Rejected));
        CHECK(canTransition(Status::InProgress, Status::Resolved));
        CHECK(canTransition(Status::InProgress, Status::Rejected));
    }

    TEST_CASE("a report can't go back to New or stay where it is") {
        CHECK_FALSE(canTransition(Status::InProgress, Status::New));
        CHECK_FALSE(canTransition(Status::New, Status::New));
        CHECK_FALSE(canTransition(Status::InProgress, Status::InProgress));
    }

    TEST_CASE("a closed report can't change any more") {
        for (const Status closed : {Status::Resolved, Status::Rejected}) {
            for (const Status next : {Status::New, Status::InProgress, Status::Resolved, Status::Rejected}) {
                CHECK_FALSE(canTransition(closed, next));
            }
        }
    }
}

TEST_SUITE("Report") {
    TEST_CASE("a new report keeps what it was created with and starts as New") {
        const Report report{"R-0007", Category::Garbage, "Bags on the pavement", kChisinau, at(2026, 10, 1)};

        CHECK(report.id() == "R-0007");
        CHECK(report.category() == Category::Garbage);
        CHECK(report.description() == "Bags on the pavement");
        CHECK(report.location() == kChisinau);
        CHECK(report.createdAt() == at(2026, 10, 1));
        CHECK(report.status() == Status::New);
        CHECK(report.isOpen());
    }

    TEST_CASE("an allowed transition changes the status") {
        Report report = makeReport();

        report.transitionTo(Status::InProgress);
        CHECK(report.status() == Status::InProgress);
        CHECK(report.isOpen());

        report.transitionTo(Status::Resolved);
        CHECK(report.status() == Status::Resolved);
        CHECK_FALSE(report.isOpen());
    }

    TEST_CASE("a transition the lifecycle forbids throws and leaves the report unchanged") {
        Report report = makeReport();
        report.transitionTo(Status::Rejected);

        CHECK_THROWS_AS(report.transitionTo(Status::InProgress), InvalidStatusTransition);
        CHECK(report.status() == Status::Rejected);
    }

    TEST_CASE("the error says which transition was refused") {
        Report report = makeReport();
        report.transitionTo(Status::Resolved);

        CHECK_THROWS_WITH(report.transitionTo(Status::New), "A report can't go from \"Resolved\" to \"New\".");
    }
}

TEST_SUITE("GeoPoint") {
    TEST_CASE("the distance from a point to itself is zero") {
        CHECK(distanceMeters(kChisinau, kChisinau) == doctest::Approx(0.0));
    }

    TEST_CASE("one degree of latitude is about 111.2 km") {
        const GeoPoint south{.latitude = 47.0, .longitude = 28.0};
        const GeoPoint north{.latitude = 48.0, .longitude = 28.0};

        CHECK(distanceMeters(south, north) == doctest::Approx(111'194.9).epsilon(0.0001));
    }

    TEST_CASE("the distance is the same in both directions") {
        CHECK(distanceMeters(kChisinau, kBucharest) == doctest::Approx(distanceMeters(kBucharest, kChisinau)));
    }

    TEST_CASE("the service area contains its inside and its border, and nothing else") {
        CHECK(kMoldova.contains(kChisinau));
        CHECK(kMoldova.contains({.latitude = kMoldova.south, .longitude = kMoldova.west}));
        CHECK_FALSE(kMoldova.contains(kBucharest));
        CHECK_FALSE(kMoldova.contains({.latitude = std::numeric_limits<double>::quiet_NaN(), .longitude = 28.0}));
    }
}

TEST_SUITE("DeadlineCalculator") {
    using std::chrono::days;
    using std::chrono::sys_days;

    TEST_CASE("the due date is 30 calendar days after the day of the report") {
        const DeadlineCalculator deadlines;
        // Reported late in the evening: the hour must not push the deadline a day further.
        const Report report{"R-0001", Category::Pothole, "", kChisinau, at(2026, 10, 1, 23)};

        CHECK(deadlines.dueDate(report) == std::chrono::floor<days>(at(2026, 10, 31)));
    }

    TEST_CASE("days left count down to zero on the due date and go negative after it") {
        const DeadlineCalculator deadlines;
        const Report report = makeReport();

        CHECK(deadlines.daysLeft(report, at(2026, 10, 1)) == 30);
        CHECK(deadlines.daysLeft(report, at(2026, 10, 30)) == 1);
        CHECK(deadlines.daysLeft(report, at(2026, 10, 31)) == 0);
        CHECK(deadlines.daysLeft(report, at(2026, 11, 2)) == -2);
    }

    TEST_CASE("a closed report has no deadline") {
        const DeadlineCalculator deadlines;
        Report report = makeReport();
        report.transitionTo(Status::Resolved);

        CHECK_FALSE(deadlines.daysLeft(report, at(2026, 10, 5)).has_value());
    }

    TEST_CASE("the term can be changed") {
        const DeadlineCalculator deadlines{days{10}};

        CHECK(deadlines.daysLeft(makeReport(), at(2026, 10, 1)) == 10);
    }
}
