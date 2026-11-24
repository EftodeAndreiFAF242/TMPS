// Lab 4 - Unit tests: at least two tests for each behavioral pattern, each one proves its key property

#include <iostream>
#include <string>
#include <type_traits>

#include "Lab1/reports/Report.h"
#include "Lab4/cases/ReportCase.h"
#include "Lab4/statuses/ClosedState.h"
#include "Lab4/statuses/FixedState.h"
#include "Lab4/statuses/InProgressState.h"
#include "Lab4/statuses/RegisteredState.h"
#include "Lab4/statuses/ReportState.h"

using namespace std;

int testsRun = 0;
int testsFailed = 0;

// Prints PASS or FAIL
void check(const string& testName, bool passed) {
    testsRun++;
    if (passed) {
        cout << "[PASS] " << testName << "\n";
    } else {
        cout << "[FAIL] " << testName << "\n";
        testsFailed++;
    }
}

// Sesizarea #7, deja salvată
Report potholeReport() {
    Report report("Pothole", "Deep pothole in front of the hospital");
    report.id = 7;
    return report;
}

// ---- State: the statuses of a case ----

void testEveryStatusIsAReportState() {
    check("State: ReportState is abstract and the four statuses are ReportStates",
          is_abstract<ReportState>::value && is_base_of<ReportState, RegisteredState>::value
              && is_base_of<ReportState, InProgressState>::value && is_base_of<ReportState, FixedState>::value
              && is_base_of<ReportState, ClosedState>::value);
}

void testFullLifeOfACase() {
    ReportCase reportCase(potholeReport());
    bool startsRegistered = reportCase.getStatus() == "Registered";

    string started = reportCase.startWork();
    bool inProgress = reportCase.getStatus() == "In progress";
    string finished = reportCase.finishWork();
    bool fixed = reportCase.getStatus() == "Fixed";
    string closed = reportCase.close();

    check("State: a case goes Registered -> In progress -> Fixed -> Closed",
          startsRegistered && started == "" && inProgress && finished == "" && fixed && closed == ""
              && reportCase.getStatus() == "Closed");
}

void testForbiddenStepsAreRefused() {
    ReportCase reportCase(potholeReport());
    string finishTooEarly = reportCase.finishWork();
    string closeTooEarly = reportCase.close();

    check("State: a new case refuses to be finished or closed, says why, and stays Registered",
          finishTooEarly == "the work can't be finished, the case is Registered."
              && closeTooEarly == "the case can't be closed, the case is Registered."
              && reportCase.getStatus() == "Registered");

    // Închidem cazul, apoi încercăm iar
    reportCase.startWork();
    reportCase.finishWork();
    reportCase.close();
    string startAfterClose = reportCase.startWork();
    string reopenAfterClose = reportCase.reopen();

    check("State: a closed case refuses every step and stays Closed",
          startAfterClose == "the work can't start, the case is Closed."
              && reopenAfterClose == "the case can't be reopened, the case is Closed."
              && reportCase.getStatus() == "Closed" && reportCase.getTimesReopened() == 0);
}

void testReopenSendsTheCrewBack() {
    ReportCase reportCase(potholeReport());
    reportCase.startWork();
    reportCase.finishWork();

    string reopened = reportCase.reopen();
    bool backInProgress = reportCase.getStatus() == "In progress";
    string fixedAgain = reportCase.finishWork();

    check("State: a fixed case can be reopened, goes back to In progress and is counted",
          reopened == "" && backInProgress && fixedAgain == "" && reportCase.getStatus() == "Fixed"
              && reportCase.getTimesReopened() == 1);
}

int main() {
    cout << "=== Unit tests of laboratory work 4: behavioral design patterns ===\n";

    cout << "\n--- State ---\n";
    testEveryStatusIsAReportState();
    testFullLifeOfACase();
    testForbiddenStepsAreRefused();
    testReopenSendsTheCrewBack();

    cout << "\n" << testsRun << " tests, " << testsRun - testsFailed << " passed, " << testsFailed
         << " failed.\n";
    return testsFailed;
}
