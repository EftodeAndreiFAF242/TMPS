// SequentialIdGenerator.cpp
// Implementation of the id generator that numbers the reports in order.

#include "infrastructure/SequentialIdGenerator.hpp"

#include <iomanip>
#include <sstream>

using namespace std;

namespace civicdesk {

ReportId SequentialIdGenerator::next() {
    ostringstream id;
    // setw(4) with setfill('0') pads the number with zeros: 1 becomes 0001.
    // ++counter_ increases the counter first, so the first id is 1 and not 0.
    id << prefix_ << '-' << setw(4) << setfill('0') << ++counter_;
    return id.str();
}

}  // namespace civicdesk
