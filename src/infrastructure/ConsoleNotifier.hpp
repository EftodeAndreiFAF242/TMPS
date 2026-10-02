// ConsoleNotifier.hpp
// Implementation of INotifier that writes the announcements as text.

#pragma once

#include "application/ports/INotifier.hpp"

#include <ostream>

using namespace std;

namespace civicdesk {

/// Announces report events as lines of text on an output stream, normally cout.
class ConsoleNotifier final : public INotifier {
public:
    /// The stream is not owned and has to outlive the notifier.
    explicit ConsoleNotifier(ostream& out) noexcept : out_{out} {}

    void reportSubmitted(const Report& report) override;
    void statusChanged(const Report& report, Status previous, string_view note) override;

private:
    ostream& out_;
};

}  // namespace civicdesk
