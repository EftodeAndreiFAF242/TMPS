// Lab 4 - Unit tests: at least two tests for each behavioral pattern, each one proves its key property

#include <ctime>
#include <iostream>
#include <sstream>
#include <string>
#include <type_traits>
#include <vector>

#include "Lab1/notifications/Notifier.h"
#include "Lab1/reports/Report.h"
#include "Lab3/calendar/SystemCalendar.h"
#include "Lab3/notifications/ArchivedNotifier.h"
#include "Lab3/notifications/MessageArchive.h"
#include "Lab3/notifications/SignedNotifier.h"
#include "Lab4/cases/CaseSnapshot.h"
#include "Lab4/cases/ReportCase.h"
#include "Lab4/statuses/ClosedState.h"
#include "Lab4/statuses/FixedState.h"
#include "Lab4/statuses/InProgressState.h"
#include "Lab4/statuses/RegisteredState.h"
#include "Lab4/statuses/ReportState.h"
#include "Lab4/updates/CaseLog.h"
#include "Lab4/updates/CaseObserver.h"
#include "Lab4/updates/CitizenUpdates.h"

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

// Notificator fals: doar ține mesajele
class RecordingNotifier : public Notifier {
public:
    void send(const string& message) override {
        messages.push_back(message);
    }

    vector<string> messages;
};

// cout goes into this string
stringstream capturedScreen;
streambuf* realScreen = nullptr;

void startCapture() {
    capturedScreen.str("");
    realScreen = cout.rdbuf(capturedScreen.rdbuf());
}

string stopCapture() {
    cout.rdbuf(realScreen);
    return capturedScreen.str();
}

// A fixed day, at noon
time_t noonOf(int day, int month, int year) {
    tm date = {};
    date.tm_mday = day;
    date.tm_mon = month - 1;     // lunile încep de la 0
    date.tm_year = year - 1900;  // anii se numără de la 1900
    date.tm_hour = 12;
    return mktime(&date);
}

// "Today" is always 20.11.2026
const SystemCalendar testCalendar(noonOf(20, 11, 2026));

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

// ---- Observer: the citizen and the log ----

void testEverySubscribedObserverIsTold() {
    RecordingNotifier recorder;
    CitizenUpdates citizen(&recorder);
    CaseLog caseLog(&testCalendar);
    ReportCase reportCase(potholeReport());
    reportCase.subscribe(&citizen);
    reportCase.subscribe(&caseLog);

    startCapture();
    reportCase.startWork();
    stopCapture();

    check("Observer: one change of status is told to every subscribed observer",
          recorder.messages.size() == 1 && recorder.messages[0] == "Your report #7 (Pothole) is now In progress."
              && caseLog.entries().size() == 1 && caseLog.entries()[0] == "20.11.2026  report #7 (Pothole): In progress");
}

void testUnsubscribedObserverIsNotTold() {
    RecordingNotifier recorder;
    CitizenUpdates citizen(&recorder);
    CaseLog caseLog(&testCalendar);
    ReportCase reportCase(potholeReport());
    reportCase.subscribe(&citizen);
    reportCase.subscribe(&caseLog);

    // Cetățeanul se dezabonează, apoi revine
    startCapture();
    reportCase.unsubscribe(&citizen);
    reportCase.startWork();
    size_t messagesWhileAway = recorder.messages.size();
    reportCase.subscribe(&citizen);
    reportCase.finishWork();
    stopCapture();

    check("Observer: an unsubscribed observer is not told, the others still are",
          messagesWhileAway == 0 && caseLog.entries().size() == 2);
    check("Observer: after subscribing again at runtime, the observer is told again",
          recorder.messages.size() == 1 && recorder.messages[0] == "Your report #7 (Pothole) is now Fixed.");
}

void testRefusedStepTellsNobody() {
    RecordingNotifier recorder;
    CitizenUpdates citizen(&recorder);
    ReportCase reportCase(potholeReport());
    reportCase.subscribe(&citizen);

    reportCase.finishWork();
    reportCase.close();

    check("Observer: a refused step changes nothing, so nobody is told", recorder.messages.empty());
}

void testCitizenUpdateGoesThroughTheLab3Decorators() {
    RecordingNotifier email;
    MessageArchive archive;
    SignedNotifier signedEmail(&email);
    ArchivedNotifier archivedEmail(&signedEmail, &archive);
    CitizenUpdates citizen(&archivedEmail);
    ReportCase reportCase(potholeReport());
    reportCase.subscribe(&citizen);

    reportCase.startWork();

    check("Observer: the citizen's update is signed and archived by the decorators of lab 3",
          email.messages.size() == 1
              && email.messages[0] == "Your report #7 (Pothole) is now In progress. -- Chisinau City Hall"
              && archive.all().size() == 1 && archive.all()[0] == "Your report #7 (Pothole) is now In progress.");
}

// ---- Memento: snapshots of a case ----

void testRestoreGivesBackTheExactState() {
    ReportCase reportCase(potholeReport());
    reportCase.startWork();
    reportCase.finishWork();
    reportCase.reopen();
    reportCase.finishWork();

    // Fixed, redeschis o dată
    CaseSnapshot snapshot = reportCase.save();
    reportCase.close();
    bool closedBefore = reportCase.getStatus() == "Closed";
    reportCase.restore(snapshot);

    check("Memento: restore() gives back the exact saved case, its status and how often it was reopened",
          closedBefore && reportCase.getStatus() == "Fixed" && reportCase.getTimesReopened() == 1);
    check("Memento: after restore() the restored status decides the next step again",
          reportCase.close() == "" && reportCase.getStatus() == "Closed");
}

void testLaterChangesDoNotTouchTheSnapshot() {
    ReportCase reportCase(potholeReport());
    CaseSnapshot snapshot = reportCase.save();

    reportCase.startWork();
    reportCase.finishWork();
    reportCase.reopen();
    reportCase.restore(snapshot);
    bool firstRestore = reportCase.getStatus() == "Registered" && reportCase.getTimesReopened() == 0;

    // Alte schimbări, aceeași copie
    reportCase.startWork();
    reportCase.finishWork();
    reportCase.restore(snapshot);

    check("Memento: changes made after save() do not change the snapshot, it can be restored again",
          firstRestore && reportCase.getStatus() == "Registered" && reportCase.getTimesReopened() == 0);
}

void testOnlyTheCaseCanMakeASnapshot() {
    check("Memento: outside code can keep a copy of a snapshot, but can't make one or fill it in",
          is_copy_constructible<CaseSnapshot>::value && !is_default_constructible<CaseSnapshot>::value
              && !is_constructible<CaseSnapshot, const ReportState*, int>::value);
}

void testRestoreIsToldToTheObservers() {
    RecordingNotifier recorder;
    CitizenUpdates citizen(&recorder);
    ReportCase reportCase(potholeReport());
    CaseSnapshot snapshot = reportCase.save();
    reportCase.startWork();
    reportCase.subscribe(&citizen);

    reportCase.restore(snapshot);

    check("Memento: after restore() the observers are told the status that came back",
          recorder.messages.size() == 1 && recorder.messages[0] == "Your report #7 (Pothole) is now Registered.");
}

int main() {
    cout << "=== Unit tests of laboratory work 4: behavioral design patterns ===\n";

    cout << "\n--- State ---\n";
    testEveryStatusIsAReportState();
    testFullLifeOfACase();
    testForbiddenStepsAreRefused();
    testReopenSendsTheCrewBack();

    cout << "\n--- Observer ---\n";
    testEverySubscribedObserverIsTold();
    testUnsubscribedObserverIsNotTold();
    testRefusedStepTellsNobody();
    testCitizenUpdateGoesThroughTheLab3Decorators();

    cout << "\n--- Memento ---\n";
    testRestoreGivesBackTheExactState();
    testLaterChangesDoNotTouchTheSnapshot();
    testOnlyTheCaseCanMakeASnapshot();
    testRestoreIsToldToTheObservers();

    cout << "\n" << testsRun << " tests, " << testsRun - testsFailed << " passed, " << testsFailed
         << " failed.\n";
    return testsFailed;
}
