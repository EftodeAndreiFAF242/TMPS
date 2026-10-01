#include "domain/Report.hpp"

#include <utility>

namespace civicdesk {

namespace {

std::string transitionMessage(Status from, Status to) {
    std::string message{"A report can't go from \""};
    message += nameOf(from);
    message += "\" to \"";
    message += nameOf(to);
    message += "\".";
    return message;
}

}  // namespace

InvalidStatusTransition::InvalidStatusTransition(Status from, Status to)
    : std::logic_error{transitionMessage(from, to)} {}

Report::Report(ReportId id, Category category, std::string description, GeoPoint location, TimePoint createdAt)
    : id_{std::move(id)},
      category_{category},
      description_{std::move(description)},
      location_{location},
      createdAt_{createdAt} {}

void Report::transitionTo(Status next) {
    if (!canTransition(status_, next)) {
        throw InvalidStatusTransition{status_, next};
    }
    status_ = next;
}

}  // namespace civicdesk
