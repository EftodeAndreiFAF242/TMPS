#pragma once

// Test doubles and small helpers shared by the test files.
//
// DIP is what makes these possible: ReportService only knows IClock and INotifier, so a
// test can hand it a clock that stands still and a notifier that remembers its calls.

#include "application/ports/IClock.hpp"
#include "application/ports/INotifier.hpp"
#include "domain/GeoPoint.hpp"
#include "domain/Report.hpp"
#include "domain/Types.hpp"

#include <chrono>
#include <string>
#include <string_view>
#include <utility>
#include <vector>

namespace civicdesk::testing {

/// A point in the centre of Chisinau, inside the service area.
inline constexpr GeoPoint kChisinau{.latitude = 47.0105, .longitude = 28.8638};

/// A point in Bucharest, outside the service area.
inline constexpr GeoPoint kBucharest{.latitude = 44.4268, .longitude = 26.1025};

/// The given calendar day (UTC) at the given hour.
inline TimePoint at(int year, unsigned month, unsigned day, int hour = 12) {
    using namespace std::chrono;
    return sys_days{std::chrono::year{year} / std::chrono::month{month} / std::chrono::day{day}} + hours{hour};
}

/// A valid draft, for tests that don't care about its contents.
inline ReportDraft potholeDraft(GeoPoint location = kChisinau) {
    return ReportDraft{.category = Category::Pothole, .description = "Pothole on the main street", .location = location};
}

/// A report with the given id, created on 1 October 2026.
inline Report makeReport(ReportId id = "R-0001", Category category = Category::Pothole, GeoPoint location = kChisinau) {
    return Report{std::move(id), category, "A problem", location, at(2026, 10, 1)};
}

/// A clock that shows whatever time the test sets.
class FixedClock final : public IClock {
public:
    explicit FixedClock(TimePoint now) noexcept : now_{now} {}

    [[nodiscard]] TimePoint now() const override { return now_; }
    void set(TimePoint now) noexcept { now_ = now; }

private:
    TimePoint now_;
};

/// A notifier that sends nothing and remembers what it was asked to announce.
class RecordingNotifier final : public INotifier {
public:
    struct StatusChange {
        ReportId id;
        Status previous;
        Status current;
        std::string note;
    };

    void reportSubmitted(const Report& report) override { submitted.push_back(report.id()); }

    void statusChanged(const Report& report, Status previous, std::string_view note) override {
        changes.push_back(StatusChange{report.id(), previous, report.status(), std::string{note}});
    }

    std::vector<ReportId> submitted;
    std::vector<StatusChange> changes;
};

}  // namespace civicdesk::testing
