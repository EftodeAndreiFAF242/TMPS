#pragma once

#include "application/ports/IClock.hpp"

#include <chrono>

namespace civicdesk {

/// The real clock of the machine.
class SystemClock final : public IClock {
public:
    [[nodiscard]] TimePoint now() const override { return std::chrono::system_clock::now(); }
};

}  // namespace civicdesk
