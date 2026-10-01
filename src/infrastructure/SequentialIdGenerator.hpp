#pragma once

#include "application/ports/IIdGenerator.hpp"

#include <string>
#include <utility>

namespace civicdesk {

/// Numbers the reports in order: R-0001, R-0002, R-0003 and so on.
class SequentialIdGenerator final : public IIdGenerator {
public:
    explicit SequentialIdGenerator(std::string prefix = "R") : prefix_{std::move(prefix)} {}

    [[nodiscard]] ReportId next() override;

private:
    std::string prefix_;
    unsigned long long counter_{0};
};

}  // namespace civicdesk
