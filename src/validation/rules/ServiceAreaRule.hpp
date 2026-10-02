// ServiceAreaRule.hpp
// Validation rule: the report has to be located inside the service area.

#pragma once

#include "domain/GeoPoint.hpp"
#include "validation/IValidationRule.hpp"

namespace civicdesk {

/// The report has to be located where a city hall can act on it.
class ServiceAreaRule final : public IValidationRule {
public:
    explicit ServiceAreaRule(ServiceArea area) noexcept : area_{area} {}

    void check(const ReportDraft& draft, ValidationResult& result) const override;

private:
    ServiceArea area_;
};

}  // namespace civicdesk
