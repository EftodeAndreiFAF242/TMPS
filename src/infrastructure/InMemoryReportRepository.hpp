// InMemoryReportRepository.hpp
// Implementation of IReportRepository that keeps the reports in memory.

#pragma once

#include "application/ports/IReportRepository.hpp"

#include <vector>

using namespace std;

namespace civicdesk {

/// Keeps the reports in memory, in the order they were first saved.
/// Enough for the laboratory and for tests; the data is gone when the program ends.
class InMemoryReportRepository final : public IReportRepository {
public:
    void save(const Report& report) override;
    [[nodiscard]] optional<Report> findById(const ReportId& id) const override;
    [[nodiscard]] vector<Report> findAll(const IReportSpecification& specification) const override;

private:
    vector<Report> reports_;
};

}  // namespace civicdesk
