#pragma once

#include "application/ports/INotifier.hpp"

#include <ostream>

namespace civicdesk {

/// Announces report events as lines of text on an output stream, normally std::cout.
class ConsoleNotifier final : public INotifier {
public:
    /// The stream is not owned and has to outlive the notifier.
    explicit ConsoleNotifier(std::ostream& out) noexcept : out_{out} {}

    void reportSubmitted(const Report& report) override;
    void statusChanged(const Report& report, Status previous, std::string_view note) override;

private:
    std::ostream& out_;
};

}  // namespace civicdesk
