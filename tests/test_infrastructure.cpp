#include "infrastructure/ConsoleNotifier.hpp"
#include "infrastructure/InMemoryReportRepository.hpp"
#include "infrastructure/SequentialIdGenerator.hpp"
#include "specification/Specifications.hpp"
#include "support/Fakes.hpp"

#include <doctest/doctest.h>

#include <sstream>
#include <vector>

using namespace civicdesk;
using namespace civicdesk::testing;

TEST_SUITE("InMemoryReportRepository") {
    TEST_CASE("a saved report can be found by its id") {
        InMemoryReportRepository repository;
        repository.save(makeReport("R-0001"));

        CHECK(repository.findById("R-0001").has_value());
        CHECK_FALSE(repository.findById("R-0002").has_value());
    }

    TEST_CASE("saving a report with an existing id replaces it and keeps its place") {
        InMemoryReportRepository repository;
        repository.save(makeReport("R-0001"));
        repository.save(makeReport("R-0002"));

        Report updated = makeReport("R-0001");
        updated.transitionTo(Status::InProgress);
        repository.save(updated);

        const std::vector<Report> all = repository.findAll(AnyReport{});
        REQUIRE(all.size() == 2);
        CHECK(all[0].id() == "R-0001");
        CHECK(all[0].status() == Status::InProgress);
        CHECK(all[1].id() == "R-0002");
    }

    TEST_CASE("the repository hands out copies, so changing one doesn't change what is stored") {
        InMemoryReportRepository repository;
        repository.save(makeReport("R-0001"));

        Report copy = *repository.findById("R-0001");
        copy.transitionTo(Status::Resolved);

        CHECK(repository.findById("R-0001")->status() == Status::New);
    }

    TEST_CASE("findAll filters by the specification") {
        InMemoryReportRepository repository;
        repository.save(makeReport("R-0001", Category::Pothole));
        repository.save(makeReport("R-0002", Category::Garbage));
        repository.save(makeReport("R-0003", Category::Pothole));

        const std::vector<Report> potholes = repository.findAll(HasCategory{Category::Pothole});

        REQUIRE(potholes.size() == 2);
        CHECK(potholes[0].id() == "R-0001");
        CHECK(potholes[1].id() == "R-0003");
    }
}

TEST_SUITE("SequentialIdGenerator") {
    TEST_CASE("ids count up from 1, padded to four digits") {
        SequentialIdGenerator ids{"R"};

        CHECK(ids.next() == "R-0001");
        CHECK(ids.next() == "R-0002");
    }

    TEST_CASE("the prefix can be changed") {
        SequentialIdGenerator ids{"CHS"};

        CHECK(ids.next() == "CHS-0001");
    }
}

TEST_SUITE("ConsoleNotifier") {
    TEST_CASE("a submitted report is announced with its id and category") {
        std::ostringstream out;
        ConsoleNotifier notifier{out};

        notifier.reportSubmitted(makeReport("R-0001", Category::StreetLight));

        CHECK(out.str() == "[notify] R-0001 received: Street light\n");
    }

    TEST_CASE("a status change is announced with both statuses and the note") {
        std::ostringstream out;
        ConsoleNotifier notifier{out};
        Report report = makeReport("R-0001");
        report.transitionTo(Status::InProgress);

        SUBCASE("with a note") {
            notifier.statusChanged(report, Status::New, "On it");

            CHECK(out.str() == "[notify] R-0001: New -> In progress (\"On it\")\n");
        }

        SUBCASE("without a note") {
            notifier.statusChanged(report, Status::New, "");

            CHECK(out.str() == "[notify] R-0001: New -> In progress\n");
        }
    }
}
