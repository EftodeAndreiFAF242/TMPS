#pragma once

#include "domain/Report.hpp"

namespace civicdesk {

/// A yes-or-no question about a report: "is it open?", "is it a pothole?", "is it near here?".
///
/// OCP: searching is extended by writing a new specification. The repository has a single
/// query method that takes any specification, so its interface never grows a new
/// findByThis or findByThat method.
class IReportSpecification {
public:
    virtual ~IReportSpecification() = default;

    [[nodiscard]] virtual bool isSatisfiedBy(const Report& report) const = 0;
};

}  // namespace civicdesk
