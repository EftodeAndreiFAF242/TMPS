// ReportService.cpp
// Implementation of the use cases. Every method here only decides the order of the steps;
// the steps themselves are done by the classes the service was given.

#include "application/ReportService.hpp"

#include "specification/Specifications.hpp"
#include "support/Text.hpp"

#include <memory>
#include <utility>

using namespace std;

namespace civicdesk {

ReportNotFound::ReportNotFound(const ReportId& id) : runtime_error{"There is no report with the id " + id + "."} {}

RejectionReasonRequired::RejectionReasonRequired()
    : invalid_argument{"A rejection needs a reason. The citizen sees it."} {}

// DIP: the constructor receives interfaces. The service stores the references and never
// finds out which concrete classes stand behind them.
ReportService::ReportService(IReportRepository& repository,
                             INotifier& notifier,
                             const ReportValidator& validator,
                             const IClock& clock,
                             IIdGenerator& ids) noexcept
    : repository_{repository}, notifier_{notifier}, validator_{validator}, clock_{clock}, ids_{ids} {}

SubmissionResult ReportService::submit(const ReportDraft& draft) {
    // Step 1: check the draft. An invalid draft stops here, before an id is taken.
    const ValidationResult validation = validator_.validate(draft);
    if (!validation.ok()) {
        return SubmissionResult{.report = nullopt, .errors = validation.errors()};
    }

    // Step 2: turn the draft into a report, with a fresh id and the current time.
    Report report{ids_.next(), draft.category, draft.description, draft.location, clock_.now()};

    // Step 3: store it, then announce it.
    repository_.save(report);
    notifier_.reportSubmitted(report);

    return SubmissionResult{.report = move(report), .errors = {}};
}

Report ReportService::changeStatus(const ReportId& id, Status next, string_view note) {
    optional<Report> report = repository_.findById(id);
    if (!report) {
        throw ReportNotFound{id};
    }
    // The citizen reads the note, so a rejection without one explains nothing.
    if (next == Status::Rejected && isBlank(note)) {
        throw RejectionReasonRequired{};
    }

    // transitionTo throws if the lifecycle forbids the move. It is called before save and
    // before the notifier, so a refused change never reaches the repository or the citizen.
    const Status previous = report->status();
    report->transitionTo(next);

    repository_.save(*report);
    notifier_.statusChanged(*report, previous, note);

    return move(*report);
}

optional<Report> ReportService::findById(const ReportId& id) const {
    return repository_.findById(id);
}

vector<Report> ReportService::search(const IReportSpecification& specification) const {
    return repository_.findAll(specification);
}

vector<Report> ReportService::possibleDuplicates(const ReportDraft& draft) const {
    // OCP: a new kind of search built only by combining existing conditions. The
    // repository was not changed for it.
    AllOf sameProblemNearby;
    sameProblemNearby.add(make_unique<HasCategory>(draft.category))
        .add(make_unique<IsOpen>())
        .add(make_unique<WithinRadius>(draft.location, kDuplicateRadiusMeters));

    return repository_.findAll(sameProblemNearby);
}

}  // namespace civicdesk
