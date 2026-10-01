#pragma once

#include "domain/Types.hpp"

namespace civicdesk {

/// The source of the current time.
///
/// DIP: asking the operating system for the time is a hidden dependency. Behind an
/// interface it becomes an explicit one, and a test can set the clock to any date.
class IClock {
public:
    virtual ~IClock() = default;

    [[nodiscard]] virtual TimePoint now() const = 0;
};

}  // namespace civicdesk
