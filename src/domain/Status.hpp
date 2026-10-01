#pragma once

#include <string_view>

namespace civicdesk {

/// Where a report stands in its lifecycle.
///
///   New ---> InProgress ---> Resolved
///    |           |
///    +-----------+---------> Rejected
///
/// Resolved and Rejected are final: a closed report never changes again.
enum class Status {
    New,
    InProgress,
    Resolved,
    Rejected,
};

/// Human-readable name of a status.
[[nodiscard]] constexpr std::string_view nameOf(Status status) noexcept {
    switch (status) {
        case Status::New:        return "New";
        case Status::InProgress: return "In progress";
        case Status::Resolved:   return "Resolved";
        case Status::Rejected:   return "Rejected";
    }
    return "Unknown";
}

/// A closed report was either fixed or refused; city hall has nothing left to do with it.
[[nodiscard]] constexpr bool isClosed(Status status) noexcept {
    return status == Status::Resolved || status == Status::Rejected;
}

/// Whether the lifecycle allows going from one status to another.
/// A report only moves forward: it can't return to New and it can't leave a closed status.
[[nodiscard]] constexpr bool canTransition(Status from, Status to) noexcept {
    if (isClosed(from) || from == to) {
        return false;
    }
    return to != Status::New;
}

}  // namespace civicdesk
