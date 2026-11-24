// "Change an object's behavior when its internal state changes"
// Lab 4 - State: the Context, the case of one report, followed until it is closed (and the Subject of Observer)

#include "Lab4/cases/ReportCase.h"

#include "Lab1/reports/Report.h"
#include "Lab4/statuses/RegisteredState.h"
#include "Lab4/updates/CaseObserver.h"

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
    notifyObservers();
    return "";
}

void ReportCase::subscribe(CaseObserver* observer) {
    observers.push_back(observer);
}

void ReportCase::unsubscribe(CaseObserver* observer) {
    // Scoatem doar observatorul cerut
    for (size_t i = 0; i < observers.size(); i++) {
        if (observers[i] == observer) {
            observers.erase(observers.begin() + i);
            return;
        }
    }
}

void ReportCase::notifyObservers() const {
    // Everyone subscribed hears it
    for (CaseObserver* observer : observers) {
        observer->caseChanged(*this);
    }
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
