// Lab 3 - Unit tests: at least two tests for each structural pattern, each one proves its key property

#include <ctime>
#include <iostream>
#include <memory>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

#include "Lab1/notifications/ConsoleNotifier.h"
#include "Lab1/notifications/EmailNotifier.h"
#include "Lab1/notifications/Notifier.h"
#include "Lab1/storage/ReportStorage.h"
#include "Lab2/crews/Crew.h"
#include "Lab2/crews/ElectricianCrew.h"
#include "Lab2/crews/GarbageCrew.h"
#include "Lab2/crews/RoadCrew.h"
#include "Lab2/departments/LightingDepartment.h"
#include "Lab2/departments/RoadDepartment.h"
#include "Lab2/workorders/WorkOrder.h"
#include "Lab3/calendar/Calendar.h"
#include "Lab3/calendar/SystemCalendar.h"
#include "Lab3/crews/CrewTeam.h"
#include "Lab3/departments/StormDepartment.h"
#include "Lab3/notifications/ArchivedNotifier.h"
#include "Lab3/notifications/MessageArchive.h"
#include "Lab3/notifications/SignedNotifier.h"
#include "Lab3/services/CityHall.h"

using namespace std;

int testsRun = 0;
int testsFailed = 0;

// Shows the result of one test. The program returns the number of failed tests, so 0 means all passed.
void check(const string& testName, bool passed) {
    testsRun++;
    if (passed) {
        cout << "[PASS] " << testName << "\n";
    } else {
        cout << "[FAIL] " << testName << "\n";
        testsFailed++;
    }
}

// A stub made only for the tests: a notifier that sends nothing and only remembers the messages.
class RecordingNotifier : public Notifier {
public:
    void send(const string& message) override {
        messages.push_back(message);
    }

    vector<string> messages;
};

// While a test captures the screen, everything written with cout goes into this text instead.
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

// True if both texts are on the screen and the first one was written before the second one.
bool comesBefore(const string& screen, const string& first, const string& second) {
    size_t firstPosition = screen.find(first);
    size_t secondPosition = screen.find(second);
    return firstPosition != string::npos && secondPosition != string::npos && firstPosition < secondPosition;
}

// The time of a day at noon, made with the C library, so the calendar tests always count from the
// same day, whatever day they run on.
time_t noonOf(int day, int month, int year) {
    tm date = {};
    date.tm_mday = day;
    date.tm_mon = month - 1;     // in the C library the months start at 0
    date.tm_year = year - 1900;  // and the years are counted from 1900
    date.tm_hour = 12;
    return mktime(&date);
}

// The calendar every test uses: "today" is always 20 November 2026.
const SystemCalendar testCalendar(noonOf(20, 11, 2026));

// ---- Adapter: SystemCalendar adapts the time functions of the C library to Calendar ----

void testDateInAFewDays() {
    const Calendar* calendar = &testCalendar;  // used only through the interface, like CityHall does

    check("Adapter: dateIn() turns the C library's time into the date the project wants",
          calendar->dateIn(0) == "20.11.2026" && calendar->dateIn(2) == "22.11.2026");
}

void testDateMovesIntoTheNextMonthAndYear() {
    check("Adapter: mktime turns 31 November into 01.12.2026, and 32 December into 01.01.2027",
          testCalendar.dateIn(11) == "01.12.2026" && testCalendar.dateIn(42) == "01.01.2027");
}

void testCityHallWritesTheDeadlineDate() {
    ReportStorage storage;
    RecordingNotifier recorder;

    startCapture();
    CityHall cityHall(&storage, &recorder, &testCalendar);
    RoadDepartment roads;
    cityHall.addDepartment("Pothole", &roads);
    cityHall.reportProblem("Pothole", "Deep pothole in front of the hospital", "Ismail St. 40", true);
    cityHall.reportProblem("Pothole", "A deep pothole in front of 3 Columna St.", "Columna St. 3", false);
    string screen = stopCapture();

    check("Adapter: city hall writes the real date on the work order, 2 days and 7 days after today",
          screen.find("done by:  22.11.2026") != string::npos && screen.find("done by:  27.11.2026") != string::npos);
}

// ---- Decorator: SignedNotifier and ArchivedNotifier wrap any Notifier ----

void testSignatureIsAdded() {
    RecordingNotifier recorder;
    SignedNotifier signedNotifier(&recorder);

    signedNotifier.send("Report #1 was registered.");

    check("Decorator: SignedNotifier adds the signature and passes the message to the wrapped notifier",
          recorder.messages.size() == 1
              && recorder.messages[0] == "Report #1 was registered. -- Chisinau City Hall");
}

void testDecoratorsWorkInAnyOrder() {
    // Order 1: the archive is outside the signature, so it keeps the text before it is signed.
    RecordingNotifier recorder1;
    MessageArchive archive1;
    SignedNotifier signed1(&recorder1);
    ArchivedNotifier archiveOutside(&signed1, &archive1);
    archiveOutside.send("Hello");

    // Order 2: the signature is outside the archive, so the archive keeps the signed text.
    RecordingNotifier recorder2;
    MessageArchive archive2;
    ArchivedNotifier archiveInside(&recorder2, &archive2);
    SignedNotifier signed2(&archiveInside);
    signed2.send("Hello");

    check("Decorator: in both orders the citizen gets the signed message",
          recorder1.messages.size() == 1 && recorder1.messages[0] == "Hello -- Chisinau City Hall"
              && recorder2.messages.size() == 1 && recorder2.messages[0] == "Hello -- Chisinau City Hall");
    check("Decorator: the order of the decorators decides what the archive keeps",
          archive1.all().size() == 1 && archive1.all()[0] == "Hello"
              && archive2.all().size() == 1 && archive2.all()[0] == "Hello -- Chisinau City Hall");
}

void testDecoratorWorksAroundAnyNotifier() {
    ConsoleNotifier console;
    EmailNotifier email;
    SignedNotifier signedConsole(&console);
    SignedNotifier signedEmail(&email);

    startCapture();
    signedConsole.send("Report #2 was registered.");
    signedEmail.send("Report #2 was registered.");
    string screen = stopCapture();

    check("Decorator: the same signature works around the console and around e-mail, without changing them",
          screen == "[console] Report #2 was registered. -- Chisinau City Hall\n"
                    "[e-mail] Report #2 was registered. -- Chisinau City Hall\n");
}

// ---- Composite: CrewTeam is a Crew made of other crews ----

// What a crew writes on the screen when it does a work order. It takes any Crew, so it is the same
// code for one crew and for a team, like Department::handle() in lab 2.
string workOf(const Crew& crew) {
    WorkOrder order;
    order.address = "Grenoble St. 120";
    startCapture();
    crew.work(order);
    return stopCapture();
}

void testTeamAndSingleCrewUseTheSameInterface() {
    RoadCrew roadCrew;
    CrewTeam team;
    team.add(make_unique<RoadCrew>());
    team.add(make_unique<GarbageCrew>());

    string oneCrew = workOf(roadCrew);
    string twoCrews = workOf(team);

    check("Composite: one crew and a team are used through the same Crew interface",
          oneCrew == "the road crew fills the pothole at Grenoble St. 120.\n"
              && twoCrews.find("the road crew fills the pothole at Grenoble St. 120.") != string::npos
              && twoCrews.find("the garbage crew cleans up at Grenoble St. 120.") != string::npos);
}

void testTeamInsideATeam() {
    unique_ptr<CrewTeam> stormTeam = make_unique<CrewTeam>();
    stormTeam->add(make_unique<RoadCrew>());
    stormTeam->add(make_unique<GarbageCrew>());

    CrewTeam bigTeam;
    bigTeam.add(make_unique<ElectricianCrew>());
    bigTeam.add(move(stormTeam));

    string screen = workOf(bigTeam);

    check("Composite: a team inside a team works too, every crew in the tree does its job",
          screen.find("the electricians repair the street light") != string::npos
              && screen.find("the road crew fills the pothole") != string::npos
              && screen.find("the garbage crew cleans up") != string::npos);
}

void testStormDepartmentSendsATeamThroughCityHall() {
    ReportStorage storage;
    RecordingNotifier recorder;

    startCapture();
    CityHall cityHall(&storage, &recorder, &testCalendar);
    StormDepartment storm;
    cityHall.addDepartment("Storm damage", &storm);
    bool accepted = cityHall.reportProblem("Storm damage", "A tree fell across the road after the storm",
                                           "Grenoble St. 120", true);
    string screen = stopCapture();

    check("Composite: city hall sends the storm team the same way it sends one crew",
          accepted && screen.find("a team of 2 crews goes out") != string::npos
              && comesBefore(screen, "the road crew fills the pothole", "the garbage crew cleans up"));
}

// ---- Facade: CityHall hides the classes of lab 1 and lab 2 behind reportProblem() ----

void testAcceptedReportGoesThroughEveryStepInOrder() {
    ReportStorage storage;
    ConsoleNotifier console;

    startCapture();
    CityHall cityHall(&storage, &console, &testCalendar);
    RoadDepartment roads;
    cityHall.addDepartment("Pothole", &roads);
    bool accepted = cityHall.reportProblem("Pothole", "Deep pothole in front of the hospital",
                                           "Ismail St. 40", true);
    string screen = stopCapture();

    check("Facade: one call to reportProblem() saves the report", accepted && storage.all().size() == 1);
    check("Facade: the steps run in the right order: citizen told, work order, truck, crew",
          comesBefore(screen, "Report #1 was registered.", "Work order for report #1")
              && comesBefore(screen, "Work order for report #1", "Truck #1 goes out.")
              && comesBefore(screen, "Truck #1 goes out.", "the road crew fills the pothole"));
}

void testRefusedReportGetsNoWorkOrder() {
    ReportStorage storage;
    RecordingNotifier recorder;

    startCapture();
    CityHall cityHall(&storage, &recorder, &testCalendar);
    RoadDepartment roads;
    cityHall.addDepartment("Pothole", &roads);
    bool accepted = cityHall.reportProblem("Pothole", "Hole", "Ismail St. 40", false);
    string screen = stopCapture();

    check("Facade: a refused report is not saved and gets no work order",
          !accepted && storage.all().empty() && screen.find("Work order") == string::npos);
    check("Facade: the citizen is told why the report was refused",
          recorder.messages.size() == 1
              && recorder.messages[0] == "Report refused: The description must have at least 10 characters.");
}

void testEachCategoryGoesToItsDepartment() {
    ReportStorage storage;
    RecordingNotifier recorder;

    startCapture();
    CityHall cityHall(&storage, &recorder, &testCalendar);
    RoadDepartment roads;
    LightingDepartment lighting;
    cityHall.addDepartment("Pothole", &roads);
    cityHall.addDepartment("Street light", &lighting);
    cityHall.reportProblem("Street light", "The street light near the school is blinking",
                           "Mihai Viteazul St. 7", false);
    string screen = stopCapture();

    check("Facade: the department added for the category is the one that sends its crew",
          screen.find("the electricians repair the street light") != string::npos
              && screen.find("the road crew") == string::npos);
}

void testNewDepartmentMakesItsCategoryKnown() {
    ReportStorage storage;
    RecordingNotifier recorder;

    startCapture();
    CityHall cityHall(&storage, &recorder, &testCalendar);
    RoadDepartment roads;
    cityHall.addDepartment("Pothole", &roads);
    bool before = cityHall.reportProblem("Street light", "The street light near the school is blinking",
                                         "Mihai Viteazul St. 7", false);
    LightingDepartment lighting;
    cityHall.addDepartment("Street light", &lighting);
    bool after = cityHall.reportProblem("Street light", "The street light near the school is blinking",
                                        "Mihai Viteazul St. 7", false);
    stopCapture();

    check("Facade: a category with no department is refused, and the citizen is told why",
          !before && recorder.messages.size() >= 1
              && recorder.messages[0] == "Report refused: \"Street light\" is not a known category.");
    check("Facade: after addDepartment() the same category is accepted, and CityHall did not change",
          after && storage.all().size() == 1);
}

int main() {
    cout << "=== Unit tests of laboratory work 3: structural design patterns ===\n";

    cout << "\n--- Adapter ---\n";
    testDateInAFewDays();
    testDateMovesIntoTheNextMonthAndYear();
    testCityHallWritesTheDeadlineDate();

    cout << "\n--- Decorator ---\n";
    testSignatureIsAdded();
    testDecoratorsWorkInAnyOrder();
    testDecoratorWorksAroundAnyNotifier();

    cout << "\n--- Composite ---\n";
    testTeamAndSingleCrewUseTheSameInterface();
    testTeamInsideATeam();
    testStormDepartmentSendsATeamThroughCityHall();

    cout << "\n--- Facade ---\n";
    testAcceptedReportGoesThroughEveryStepInOrder();
    testRefusedReportGetsNoWorkOrder();
    testEachCategoryGoesToItsDepartment();
    testNewDepartmentMakesItsCategoryKnown();

    cout << "\n" << testsRun << " tests, " << testsRun - testsFailed << " passed, " << testsFailed
         << " failed.\n";
    return testsFailed;
}
