#pragma once

#include "application/ports/IClock.hpp"
#include "application/ports/IIdGenerator.hpp"
#include "application/ports/INotifier.hpp"
#include "application/ports/IReportRepository.hpp"
#include "domain/Report.hpp"
#include "domain/Status.hpp"
#include "domain/Types.hpp"
#include "specification/IReportSpecification.hpp"
#include "validation/ReportValidator.hpp"

#include <optional>
#include <stdexcept>
#include <string>
#include <string_view>
#include <vector>

namespace civicdesk {

/// Thrown when no report has the requested id.
class ReportNotFound : public std::runtime_error {
public:
    explicit ReportNotFound(const ReportId& id);
};

/// Thrown when a report is rejected without telling the citizen why.
class RejectionReasonRequired : public std::invalid_argument {
public:
    RejectionReasonRequired();
};

/// The outcome of submitting a draft: the stored report, or the reasons it was refused.
struct SubmissionResult {
    std::optional<Report> report;
    std::vector<std::string> errors;

    [[nodiscard]] bool accepted() const noexcept { return report.has_value(); }
};

/// The use cases of the system: submit a report, change its status, search.
///
/// SRP: the service only coordinates. It decides the order of the steps and leaves each
/// step to the class that owns it: validating to ReportValidator, the lifecycle to
/// Report, storing to the repository, announcing to the notifier.
///
/// DIP: this is the high-level policy of the application, and it depends on four
/// interfaces instead of on concrete storage, output, time or id classes. The concrete
/// classes are chosen in one place, the composition root in app/main.cpp.
class ReportService {
public:
    /// Two open reports of the same category closer than this are taken as the same problem.
    static constexpr double kDuplicateRadiusMeters = 25.0;

    /// The service keeps references to its collaborators and does not own them, so they
    /// have to outlive it.
    ReportService(IReportRepository& repository,
                  INotifier& notifier,
                  const ReportValidator& validator,
                  const IClock& clock,
                  IIdGenerator& ids) noexcept;

    /// Validates the draft and, if it is valid, stores it as a new report and announces it.
    /// An invalid draft is not stored and nobody is notified.
    SubmissionResult submit(const ReportDraft& draft);

    /// Moves a report to another status and announces the change.
    /// @param note  the message for the citizen; required when the report is rejected
    /// @throws ReportNotFound           if no report has this id
    /// @throws RejectionReasonRequired  if the report is rejected without a note
    /// @throws InvalidStatusTransition  if the lifecycle doesn't allow the move
    Report changeStatus(const ReportId& id, Status next, std::string_view note = {});

    [[nodiscard]] std::optional<Report> findById(const ReportId& id) const;

    /// Every report that satisfies the specification, oldest first.
    [[nodiscard]] std::vector<Report> search(const IReportSpecification& specification) const;

    /// Open reports of the same category located next to the draft. The citizen can then
    /// join an existing report instead of sending the same problem a second time.
    [[nodiscard]] std::vector<Report> possibleDuplicates(const ReportDraft& draft) const;

private:
    IReportRepository& repository_;
    INotifier& notifier_;
    const ReportValidator& validator_;
    const IClock& clock_;
    IIdGenerator& ids_;
};

}  // namespace civicdesk
