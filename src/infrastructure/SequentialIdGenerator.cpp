#include "infrastructure/SequentialIdGenerator.hpp"

#include <iomanip>
#include <sstream>

namespace civicdesk {

ReportId SequentialIdGenerator::next() {
    std::ostringstream id;
    id << prefix_ << '-' << std::setw(4) << std::setfill('0') << ++counter_;
    return id.str();
}

}  // namespace civicdesk
