// InMemoryReportRepository.cpp
// Implementation of the repository that keeps the reports in a vector.

#include "infrastructure/InMemoryReportRepository.hpp"

#include <algorithm>
#include <iterator>

using namespace std;

namespace civicdesk {

void InMemoryReportRepository::save(const Report& report) {
    // &Report::id tells find to compare the id of each stored report with the given id.
    const auto existing = ranges::find(reports_, report.id(), &Report::id);
    if (existing != reports_.end()) {
        // Known id: replace the stored report and keep its place in the order.
        *existing = report;
    } else {
        // New id: add the report at the end.
        reports_.push_back(report);
    }
}

optional<Report> InMemoryReportRepository::findById(const ReportId& id) const {
    const auto found = ranges::find(reports_, id, &Report::id);
    if (found == reports_.end()) {
        return nullopt;
    }
    // A copy is returned, so the caller can't change the stored report by accident.
    return *found;
}

vector<Report> InMemoryReportRepository::findAll(const IReportSpecification& specification) const {
    vector<Report> matches;
    // OCP: the repository doesn't know what the specification asks. It only keeps the
    // reports for which the answer is yes.
    ranges::copy_if(reports_, back_inserter(matches), [&specification](const Report& report) {
        return specification.isSatisfiedBy(report);
    });
    return matches;
}

}  // namespace civicdesk
