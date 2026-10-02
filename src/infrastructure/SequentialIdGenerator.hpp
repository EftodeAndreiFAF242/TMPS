// SequentialIdGenerator.hpp
// Implementation of IIdGenerator that numbers the reports in order.

#pragma once

#include "application/ports/IIdGenerator.hpp"

#include <string>
#include <utility>

using namespace std;

namespace civicdesk {

/// Numbers the reports in order: R-0001, R-0002, R-0003 and so on.
class SequentialIdGenerator final : public IIdGenerator {
public:
    explicit SequentialIdGenerator(string prefix = "R") : prefix_{move(prefix)} {}

    [[nodiscard]] ReportId next() override;

private:
    string prefix_;
    unsigned long long counter_{0};
};

}  // namespace civicdesk
