// Report.cpp
// Implementation of the Report entity and of the error thrown on a forbidden status change.

#include "domain/Report.hpp"

#include <utility>

using namespace std;

namespace civicdesk {

namespace {

// Builds the text of the error, for example: A report can't go from "Resolved" to "New".
string transitionMessage(Status from, Status to) {
    string message{"A report can't go from \""};
    message += nameOf(from);
    message += "\" to \"";
    message += nameOf(to);
    message += "\".";
    return message;
}

}  // namespace

InvalidStatusTransition::InvalidStatusTransition(Status from, Status to)
    : logic_error{transitionMessage(from, to)} {}

// The id and the description are moved in, not copied. The status is not a parameter: a
// report always starts as New (see the default value of status_ in the header).
Report::Report(ReportId id, Category category, string description, GeoPoint location, TimePoint createdAt)
    : id_{move(id)},
      category_{category},
      description_{move(description)},
      location_{location},
      createdAt_{createdAt} {}

// The rules of the lifecycle live in canTransition (Status.hpp). Here they are enforced:
// the status changes only if the move is allowed, otherwise the report stays as it was.
void Report::transitionTo(Status next) {
    if (!canTransition(status_, next)) {
        throw InvalidStatusTransition{status_, next};
    }
    status_ = next;
}

}  // namespace civicdesk
