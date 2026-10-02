// Specifications.hpp
// The search conditions available so far, and AllOf, which combines them.

#pragma once

#include "domain/Category.hpp"
#include "domain/GeoPoint.hpp"
#include "domain/Status.hpp"
#include "specification/IReportSpecification.hpp"

#include <memory>
#include <vector>

using namespace std;

namespace civicdesk {

/// Matches every report.
class AnyReport final : public IReportSpecification {
public:
    [[nodiscard]] bool isSatisfiedBy(const Report& report) const override;
};

/// Matches the reports of one category.
class HasCategory final : public IReportSpecification {
public:
    explicit HasCategory(Category category) noexcept : category_{category} {}

    [[nodiscard]] bool isSatisfiedBy(const Report& report) const override;

private:
    Category category_;
};

/// Matches the reports that are in one status.
class HasStatus final : public IReportSpecification {
public:
    explicit HasStatus(Status status) noexcept : status_{status} {}

    [[nodiscard]] bool isSatisfiedBy(const Report& report) const override;

private:
    Status status_;
};

/// Matches the reports city hall still has to act on.
class IsOpen final : public IReportSpecification {
public:
    [[nodiscard]] bool isSatisfiedBy(const Report& report) const override;
};

/// Matches the reports located at most `radiusMeters` away from a point.
class WithinRadius final : public IReportSpecification {
public:
    WithinRadius(GeoPoint center, double radiusMeters) noexcept : center_{center}, radiusMeters_{radiusMeters} {}

    [[nodiscard]] bool isSatisfiedBy(const Report& report) const override;

private:
    GeoPoint center_;
    double radiusMeters_;
};

/// Matches the reports that satisfy every one of its parts (a logical AND).
/// With no parts it matches everything.
class AllOf final : public IReportSpecification {
public:
    /// Adds one more condition. Returns the specification, so calls can be chained.
    AllOf& add(unique_ptr<IReportSpecification> part);

    [[nodiscard]] bool isSatisfiedBy(const Report& report) const override;

private:
    vector<unique_ptr<IReportSpecification>> parts_;
};

}  // namespace civicdesk
