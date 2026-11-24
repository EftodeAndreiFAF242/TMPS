// "Change an object's behavior when its internal state changes"
// Lab 4 - State: the Context, the case of one report, followed until it is closed

#include "Lab4/cases/ReportCase.h"

#include "Lab1/reports/Report.h"
#include "Lab4/statuses/RegisteredState.h"

using namespace std;

ReportCase::ReportCase(const Report& report) {
    // Every case starts as Registered
    static const RegisteredState registered;
    this->reportId = report.id;
    this->category = report.category;
    this->state = &registered;
    this->timesReopened = 0;
}

string ReportCase::startWork() {
    return moveTo(state->startWork(), "the work can't start");
}

string ReportCase::finishWork() {
    return moveTo(state->finishWork(), "the work can't be finished");
}

string ReportCase::close() {
    return moveTo(state->close(), "the case can't be closed");
}

string ReportCase::reopen() {
    // Numărăm doar redeschiderile permise
    const ReportState* next = state->reopen();
    if (next != nullptr) {
        timesReopened++;
    }
    return moveTo(next, "the case can't be reopened");
}

string ReportCase::moveTo(const ReportState* next, const string& step) {
    // nullptr means the step is forbidden
    if (next == nullptr) {
        return step + ", the case is " + state->name() + ".";
    }
    state = next;
    return "";
}

int ReportCase::getReportId() const {
    return reportId;
}

const string& ReportCase::getCategory() const {
    return category;
}

string ReportCase::getStatus() const {
    return state->name();
}

int ReportCase::getTimesReopened() const {
    return timesReopened;
}
