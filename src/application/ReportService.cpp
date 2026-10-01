#include "application/ReportService.hpp"

#include "specification/Specifications.hpp"
#include "support/Text.hpp"

#include <memory>
#include <utility>

namespace civicdesk {

ReportNotFound::ReportNotFound(const ReportId& id) : std::runtime_error{"There is no report with the id " + id + "."} {}

RejectionReasonRequired::RejectionReasonRequired()
    : std::invalid_argument{"A rejection needs a reason. The citizen sees it."} {}

ReportService::ReportService(IReportRepository& repository,
                             INotifier& notifier,
                             const ReportValidator& validator,
                             const IClock& clock,
                             IIdGenerator& ids) noexcept
    : repository_{repository}, notifier_{notifier}, validator_{validator}, clock_{clock}, ids_{ids} {}

SubmissionResult ReportService::submit(const ReportDraft& draft) {
    const ValidationResult validation = validator_.validate(draft);
    if (!validation.ok()) {
        return SubmissionResult{.report = std::nullopt, .errors = validation.errors()};
    }

    Report report{ids_.next(), draft.category, draft.description, draft.location, clock_.now()};
    repository_.save(report);
    notifier_.reportSubmitted(report);

    return SubmissionResult{.report = std::move(report), .errors = {}};
}

Report ReportService::changeStatus(const ReportId& id, Status next, std::string_view note) {
    std::optional<Report> report = repository_.findById(id);
    if (!report) {
        throw ReportNotFound{id};
    }
    if (next == Status::Rejected && isBlank(note)) {
        throw RejectionReasonRequired{};
    }

    // Everything that can fail has failed by now, so a refused change never reaches the
    // repository or the notifier.
    const Status previous = report->status();
    report->transitionTo(next);

    repository_.save(*report);
    notifier_.statusChanged(*report, previous, note);

    return std::move(*report);
}

std::optional<Report> ReportService::findById(const ReportId& id) const {
    return repository_.findById(id);
}

std::vector<Report> ReportService::search(const IReportSpecification& specification) const {
    return repository_.findAll(specification);
}

std::vector<Report> ReportService::possibleDuplicates(const ReportDraft& draft) const {
    AllOf sameProblemNearby;
    sameProblemNearby.add(std::make_unique<HasCategory>(draft.category))
        .add(std::make_unique<IsOpen>())
        .add(std::make_unique<WithinRadius>(draft.location, kDuplicateRadiusMeters));

    return repository_.findAll(sameProblemNearby);
}

}  // namespace civicdesk
