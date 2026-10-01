#pragma once

#include "domain/Report.hpp"
#include "domain/Types.hpp"
#include "specification/IReportSpecification.hpp"

#include <optional>
#include <vector>

namespace civicdesk {

/// Where reports are kept.
///
/// DIP: the application layer owns this interface and ReportService depends only on it.
/// Whether the reports live in memory, in a file or in a database is a detail that
/// implements the interface, so storage can be replaced without touching the service.
class IReportRepository {
public:
    virtual ~IReportRepository() = default;

    /// Stores the report. A report with the same id is replaced.
    virtual void save(const Report& report) = 0;

    [[nodiscard]] virtual std::optional<Report> findById(const ReportId& id) const = 0;

    /// Every report that satisfies the specification, oldest first.
    [[nodiscard]] virtual std::vector<Report> findAll(const IReportSpecification& specification) const = 0;
};

}  // namespace civicdesk
