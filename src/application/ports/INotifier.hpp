// INotifier.hpp
// Port: how report events are announced. ReportService depends on this interface, not on the console (DIP).

#pragma once

#include "domain/Report.hpp"
#include "domain/Status.hpp"

#include <string_view>

using namespace std;

namespace civicdesk {

/// Tells the outside world that something happened to a report.
///
/// DIP: ReportService announces events through this interface and never learns how they
/// are delivered. The console is one implementation; e-mail or SMS would be others.
class INotifier {
public:
    virtual ~INotifier() = default;

    virtual void reportSubmitted(const Report& report) = 0;

    /// @param report    the report, already in its new status
    /// @param previous  the status it had before the change
    /// @param note      the message city hall wrote for the citizen; may be empty
    virtual void statusChanged(const Report& report, Status previous, string_view note) = 0;
};

}  // namespace civicdesk
