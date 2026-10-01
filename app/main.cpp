// CivicDesk - console demo.
//
// This file is the composition root: the one place in the program that names concrete
// classes and wires them together. Everything below it in the dependency graph talks to
// interfaces (DIP), so replacing the storage, the notifier or the clock means changing a
// line here and nothing else.

#include "application/ReportService.hpp"
#include "domain/GeoPoint.hpp"
#include "domain/Report.hpp"
#include "infrastructure/ConsoleNotifier.hpp"
#include "infrastructure/InMemoryReportRepository.hpp"
#include "infrastructure/SequentialIdGenerator.hpp"
#include "infrastructure/SystemClock.hpp"
#include "presentation/ReportFormatter.hpp"
#include "specification/Specifications.hpp"
#include "validation/ReportValidator.hpp"
#include "validation/rules/DescriptionLengthRule.hpp"
#include "validation/rules/DescriptionRequiredRule.hpp"
#include "validation/rules/ServiceAreaRule.hpp"

#include <exception>
#include <iostream>
#include <memory>
#include <string>
#include <string_view>
#include <vector>

namespace {

using namespace civicdesk;

void printHeading(std::string_view title) {
    std::cout << "\n== " << title << " ==\n";
}

/// Sends a draft through the service and prints what came back.
void submit(ReportService& service, const ReportDraft& draft) {
    const SubmissionResult result = service.submit(draft);
    if (result.accepted()) {
        std::cout << "  accepted as " << result.report->id() << '\n';
        return;
    }
    std::cout << "  refused:\n";
    for (const std::string& error : result.errors) {
        std::cout << "    - " << error << '\n';
    }
}

/// Asks the service for a status change and prints the reason if it is refused.
void changeStatus(ReportService& service, const ReportId& id, Status next, std::string_view note = {}) {
    try {
        service.changeStatus(id, next, note);
    } catch (const std::exception& error) {
        std::cout << "  " << id << " -> " << nameOf(next) << " refused: " << error.what() << '\n';
    }
}

void printReports(const std::vector<Report>& reports, const ReportFormatter& formatter, TimePoint now) {
    for (const Report& report : reports) {
        std::cout << "  " << formatter.summary(report, now) << '\n';
    }
}

}  // namespace

int main() {
    // OCP: the validator gets its rules from outside. A new rule is one more line here.
    ReportValidator validator;
    validator.addRule(std::make_unique<ServiceAreaRule>(kMoldova))
        .addRule(std::make_unique<DescriptionLengthRule>(1000))
        .addRule(std::make_unique<DescriptionRequiredRule>(Category::Other));

    // DIP: the concrete collaborators are created here and handed to the service as interfaces.
    InMemoryReportRepository repository;
    ConsoleNotifier notifier{std::cout};
    SystemClock clock;
    SequentialIdGenerator ids{"R"};
    ReportService service{repository, notifier, validator, clock, ids};

    const ReportFormatter formatter;

    std::cout << "CivicDesk - civic issue reporting backend\n";

    printHeading("1. Citizens submit reports");
    submit(service, {Category::Pothole, "Deep pothole in front of the bus stop", {47.02450, 28.83230}});
    submit(service, {Category::StreetLight, "The street light has been off for a week", {47.01050, 28.86380}});
    submit(service, {Category::Garbage, "Garbage dumped next to the playground", {46.99800, 28.85700}});

    printHeading("2. An invalid draft is refused, with every reason listed");
    submit(service, {Category::Other, "   ", {44.42680, 26.10250}});

    printHeading("3. A repeated report is recognised before it is sent");
    const ReportDraft repeated{Category::Pothole, "Big hole near the bus stop", {47.02455, 28.83235}};
    for (const Report& existing : service.possibleDuplicates(repeated)) {
        std::cout << "  same problem as " << existing.id() << ": " << existing.description() << '\n';
    }

    printHeading("4. City hall handles the reports");
    changeStatus(service, "R-0001", Status::InProgress, "A repair crew comes on Monday");
    changeStatus(service, "R-0001", Status::Resolved);
    changeStatus(service, "R-0003", Status::Rejected);
    changeStatus(service, "R-0003", Status::Rejected, "The land is private property");
    changeStatus(service, "R-0001", Status::InProgress);
    changeStatus(service, "R-0042", Status::Resolved);

    printHeading("5. Every report");
    printReports(service.search(AnyReport{}), formatter, clock.now());

    printHeading("6. Reports still waiting for city hall");
    printReports(service.search(IsOpen{}), formatter, clock.now());

    return 0;
}
