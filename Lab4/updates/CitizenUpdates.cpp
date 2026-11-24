// "Notify dependent objects automatically when an object's state changes"
// Lab 4 - Observer: a Concrete Observer, tells the citizen the new status of the report

#include "Lab4/updates/CitizenUpdates.h"

#include <string>

#include "Lab1/notifications/Notifier.h"
#include "Lab4/cases/ReportCase.h"

using namespace std;

CitizenUpdates::CitizenUpdates(Notifier* notifier) {
    this->notifier = notifier;
}

void CitizenUpdates::caseChanged(const ReportCase& reportCase) {
    // Only reads the case, never changes it
    notifier->send("Your report #" + to_string(reportCase.getReportId()) + " (" + reportCase.getCategory()
                   + ") is now " + reportCase.getStatus() + ".");
}
