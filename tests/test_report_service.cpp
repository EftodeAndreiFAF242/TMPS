#include "application/ReportService.hpp"
#include "infrastructure/InMemoryReportRepository.hpp"
#include "infrastructure/SequentialIdGenerator.hpp"
#include "specification/Specifications.hpp"
#include "support/Fakes.hpp"
#include "validation/rules/ServiceAreaRule.hpp"

#include <doctest/doctest.h>

#include <memory>
#include <optional>
#include <vector>

using namespace civicdesk;
using namespace civicdesk::testing;

namespace {

/// A service wired with test doubles. This is the same wiring as in app/main.cpp with
/// other implementations behind the interfaces, and ReportService can't tell the difference.
struct ServiceFixture {
    InMemoryReportRepository repository;
    RecordingNotifier notifier;
    ReportValidator validator;
    FixedClock clock{at(2026, 10, 1, 9)};
    SequentialIdGenerator ids{"T"};
    ReportService service{repository, notifier, validator, clock, ids};

    ServiceFixture() { validator.addRule(std::make_unique<ServiceAreaRule>(kMoldova)); }

    /// Submits a valid draft and returns the id of the new report.
    ReportId submitValid(const ReportDraft& draft = potholeDraft()) {
        const SubmissionResult result = service.submit(draft);
        REQUIRE(result.accepted());
        return result.report->id();
    }
};

}  // namespace

TEST_SUITE("ReportService::submit") {
    TEST_CASE_FIXTURE(ServiceFixture, "a valid draft becomes a stored report") {
        const SubmissionResult result = service.submit(potholeDraft());

        REQUIRE(result.accepted());
        CHECK(result.errors.empty());
        CHECK(result.report->id() == "T-0001");
        CHECK(result.report->status() == Status::New);
        CHECK(result.report->category() == Category::Pothole);
        CHECK(result.report->description() == "Pothole on the main street");

        const std::optional<Report> stored = repository.findById("T-0001");
        REQUIRE(stored.has_value());
        CHECK(stored->description() == "Pothole on the main street");
    }

    TEST_CASE_FIXTURE(ServiceFixture, "the creation time comes from the injected clock") {
        clock.set(at(2030, 1, 15, 8));

        const SubmissionResult result = service.submit(potholeDraft());

        REQUIRE(result.accepted());
        CHECK(result.report->createdAt() == at(2030, 1, 15, 8));
    }

    TEST_CASE_FIXTURE(ServiceFixture, "each accepted report gets the next id") {
        CHECK(submitValid() == "T-0001");
        CHECK(submitValid() == "T-0002");
    }

    TEST_CASE_FIXTURE(ServiceFixture, "an accepted report is announced once") {
        submitValid();

        REQUIRE(notifier.submitted.size() == 1);
        CHECK(notifier.submitted.front() == "T-0001");
    }

    TEST_CASE_FIXTURE(ServiceFixture, "an invalid draft is not stored, not announced and uses no id") {
        const SubmissionResult refused = service.submit(potholeDraft(kBucharest));

        CHECK_FALSE(refused.accepted());
        REQUIRE(refused.errors.size() == 1);
        CHECK(refused.errors.front() == "The location is outside the service area.");
        CHECK(repository.findAll(AnyReport{}).empty());
        CHECK(notifier.submitted.empty());

        // The refused draft must not have consumed T-0001.
        CHECK(submitValid() == "T-0001");
    }
}

TEST_SUITE("ReportService::changeStatus") {
    TEST_CASE_FIXTURE(ServiceFixture, "a status change is stored and returned") {
        const ReportId id = submitValid();

        const Report changed = service.changeStatus(id, Status::InProgress);

        CHECK(changed.status() == Status::InProgress);
        CHECK(repository.findById(id)->status() == Status::InProgress);
    }

    TEST_CASE_FIXTURE(ServiceFixture, "a status change is announced with the old status and the note") {
        const ReportId id = submitValid();

        service.changeStatus(id, Status::InProgress, "A crew is on its way");

        REQUIRE(notifier.changes.size() == 1);
        const RecordingNotifier::StatusChange& change = notifier.changes.front();
        CHECK(change.id == id);
        CHECK(change.previous == Status::New);
        CHECK(change.current == Status::InProgress);
        CHECK(change.note == "A crew is on its way");
    }

    TEST_CASE_FIXTURE(ServiceFixture, "an unknown id throws ReportNotFound") {
        CHECK_THROWS_AS(service.changeStatus("T-9999", Status::Resolved), ReportNotFound);
        CHECK_THROWS_WITH(service.changeStatus("T-9999", Status::Resolved), "There is no report with the id T-9999.");
        CHECK(notifier.changes.empty());
    }

    TEST_CASE_FIXTURE(ServiceFixture, "a rejection without a reason is refused and changes nothing") {
        const ReportId id = submitValid();

        CHECK_THROWS_AS(service.changeStatus(id, Status::Rejected), RejectionReasonRequired);
        CHECK_THROWS_AS(service.changeStatus(id, Status::Rejected, "   "), RejectionReasonRequired);

        CHECK(repository.findById(id)->status() == Status::New);
        CHECK(notifier.changes.empty());
    }

    TEST_CASE_FIXTURE(ServiceFixture, "a rejection with a reason goes through") {
        const ReportId id = submitValid();

        const Report rejected = service.changeStatus(id, Status::Rejected, "Not a public road");

        CHECK(rejected.status() == Status::Rejected);
        REQUIRE(notifier.changes.size() == 1);
        CHECK(notifier.changes.front().note == "Not a public road");
    }

    TEST_CASE_FIXTURE(ServiceFixture, "a transition the lifecycle forbids is refused and changes nothing") {
        const ReportId id = submitValid();
        service.changeStatus(id, Status::Resolved);

        CHECK_THROWS_AS(service.changeStatus(id, Status::InProgress), InvalidStatusTransition);

        CHECK(repository.findById(id)->status() == Status::Resolved);
        CHECK(notifier.changes.size() == 1);
    }
}

TEST_SUITE("ReportService queries") {
    TEST_CASE_FIXTURE(ServiceFixture, "findById returns the report or nothing") {
        const ReportId id = submitValid();

        CHECK(service.findById(id).has_value());
        CHECK_FALSE(service.findById("T-9999").has_value());
    }

    TEST_CASE_FIXTURE(ServiceFixture, "search returns the reports that satisfy the specification") {
        const ReportId first = submitValid();
        const ReportId second = submitValid();
        service.changeStatus(first, Status::Resolved);

        const std::vector<Report> open = service.search(IsOpen{});

        REQUIRE(open.size() == 1);
        CHECK(open.front().id() == second);
        CHECK(service.search(AnyReport{}).size() == 2);
    }

    TEST_CASE_FIXTURE(ServiceFixture, "possibleDuplicates finds open reports of the same category nearby") {
        // 0.0001 degrees of latitude is about 11 m, 0.001 is about 111 m.
        const GeoPoint near{.latitude = kChisinau.latitude + 0.0001, .longitude = kChisinau.longitude};
        const GeoPoint far{.latitude = kChisinau.latitude + 0.001, .longitude = kChisinau.longitude};

        const ReportId nearPothole = submitValid(potholeDraft(near));
        submitValid(potholeDraft(far));
        submitValid(ReportDraft{.category = Category::Garbage, .description = "Bags", .location = near});

        SUBCASE("only the open pothole within 25 m counts") {
            const std::vector<Report> duplicates = service.possibleDuplicates(potholeDraft(kChisinau));

            REQUIRE(duplicates.size() == 1);
            CHECK(duplicates.front().id() == nearPothole);
        }

        SUBCASE("once that report is closed, a new one is not a duplicate of it") {
            service.changeStatus(nearPothole, Status::Resolved);

            CHECK(service.possibleDuplicates(potholeDraft(kChisinau)).empty());
        }
    }
}
