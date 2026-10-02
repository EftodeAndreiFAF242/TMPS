// SystemClock.hpp
// Implementation of IClock that reads the real clock of the computer.

#pragma once

#include "application/ports/IClock.hpp"

#include <chrono>

using namespace std;

namespace civicdesk {

/// The real clock of the machine.
class SystemClock final : public IClock {
public:
    [[nodiscard]] TimePoint now() const override { return chrono::system_clock::now(); }
};

}  // namespace civicdesk
