#include "infrastructure/InMemoryReportRepository.hpp"

#include <algorithm>
#include <iterator>

namespace civicdesk {

void InMemoryReportRepository::save(const Report& report) {
    const auto existing = std::ranges::find(reports_, report.id(), &Report::id);
    if (existing != reports_.end()) {
        *existing = report;
    } else {
        reports_.push_back(report);
    }
}

std::optional<Report> InMemoryReportRepository::findById(const ReportId& id) const {
    const auto found = std::ranges::find(reports_, id, &Report::id);
    if (found == reports_.end()) {
        return std::nullopt;
    }
    return *found;
}

std::vector<Report> InMemoryReportRepository::findAll(const IReportSpecification& specification) const {
    std::vector<Report> matches;
    std::ranges::copy_if(reports_, std::back_inserter(matches), [&specification](const Report& report) {
        return specification.isSatisfiedBy(report);
    });
    return matches;
}

}  // namespace civicdesk
