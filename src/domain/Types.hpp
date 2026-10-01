#pragma once

#include <chrono>
#include <string>

namespace civicdesk {

/// Unique identifier of a report, for example "R-0001".
using ReportId = std::string;

/// A moment in time. Every timestamp in the system is UTC.
using TimePoint = std::chrono::system_clock::time_point;

}  // namespace civicdesk
