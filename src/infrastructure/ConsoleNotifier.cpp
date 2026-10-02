// ConsoleNotifier.cpp
// Implementation of the notifier that writes each announcement as one line of text.

#include "infrastructure/ConsoleNotifier.hpp"

using namespace std;

namespace civicdesk {

// Example: [notify] R-0001 received: Pothole
void ConsoleNotifier::reportSubmitted(const Report& report) {
    out_ << "[notify] " << report.id() << " received: " << nameOf(report.category()) << '\n';
}

// Example: [notify] R-0001: New -> In progress ("A repair crew comes on Monday")
void ConsoleNotifier::statusChanged(const Report& report, Status previous, string_view note) {
    out_ << "[notify] " << report.id() << ": " << nameOf(previous) << " -> " << nameOf(report.status());
    // The note is optional, so the brackets are printed only when there is one.
    if (!note.empty()) {
        out_ << " (\"" << note << "\")";
    }
    out_ << '\n';
}

}  // namespace civicdesk
