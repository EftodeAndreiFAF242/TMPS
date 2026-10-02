// Report.hpp
// The Report entity, the draft a citizen fills in, and the error for a forbidden status change (SRP).

#pragma once

#include "domain/Category.hpp"
#include "domain/GeoPoint.hpp"
#include "domain/Status.hpp"
#include "domain/Types.hpp"

#include <stdexcept>
#include <string>

using namespace std;

namespace civicdesk {

/// What a citizen fills in on the report form, before the system accepts it.
struct ReportDraft {
    Category category{Category::Other};
    string description;
    GeoPoint location;
};

/// Thrown when a status change would break the report lifecycle (see canTransition).
class InvalidStatusTransition : public logic_error {
public:
    InvalidStatusTransition(Status from, Status to);
};

/// A problem reported by a citizen and accepted by the system.
///
/// SRP: this class holds the state of one report and guards its lifecycle, and that is
/// all it does. It doesn't validate the citizen's input, store itself, print itself or
/// notify anyone. Each of those jobs has its own class, so each can change on its own.
class Report {
public:
    Report(ReportId id, Category category, string description, GeoPoint location, TimePoint createdAt);

    [[nodiscard]] const ReportId& id() const noexcept { return id_; }
    [[nodiscard]] Category category() const noexcept { return category_; }
    [[nodiscard]] const string& description() const noexcept { return description_; }
    [[nodiscard]] const GeoPoint& location() const noexcept { return location_; }
    [[nodiscard]] TimePoint createdAt() const noexcept { return createdAt_; }
    [[nodiscard]] Status status() const noexcept { return status_; }

    /// An open report still waits for city hall to act on it.
    [[nodiscard]] bool isOpen() const noexcept { return !isClosed(status_); }

    /// Moves the report to another status.
    /// @throws InvalidStatusTransition if the lifecycle doesn't allow the move.
    void transitionTo(Status next);

private:
    ReportId id_;
    Category category_;
    string description_;
    GeoPoint location_;
    TimePoint createdAt_;
    Status status_{Status::New};
};

}  // namespace civicdesk
