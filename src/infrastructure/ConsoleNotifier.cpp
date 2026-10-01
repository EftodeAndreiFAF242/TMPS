#include "infrastructure/ConsoleNotifier.hpp"

namespace civicdesk {

void ConsoleNotifier::reportSubmitted(const Report& report) {
    out_ << "[notify] " << report.id() << " received: " << nameOf(report.category()) << '\n';
}

void ConsoleNotifier::statusChanged(const Report& report, Status previous, std::string_view note) {
    out_ << "[notify] " << report.id() << ": " << nameOf(previous) << " -> " << nameOf(report.status());
    if (!note.empty()) {
        out_ << " (\"" << note << "\")";
    }
    out_ << '\n';
}

}  // namespace civicdesk
