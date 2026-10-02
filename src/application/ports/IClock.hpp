// IClock.hpp
// Port: where the current time comes from. ReportService depends on this interface, not on the system clock (DIP).

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
