// Types.hpp
// Short names for two basic types used across the project: a report id and a moment in time.

#pragma once

#include <chrono>
#include <string>

using namespace std;

namespace civicdesk {

/// Unique identifier of a report, for example "R-0001".
using ReportId = string;

/// A moment in time. Every timestamp in the system is UTC.
using TimePoint = chrono::system_clock::time_point;

}  // namespace civicdesk
