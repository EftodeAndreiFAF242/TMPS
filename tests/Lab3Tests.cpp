// Lab 3 - Unit tests: at least two tests for each structural pattern, each one proves its key property

#include <cstdio>
#include <fstream>
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
#include "Lab3/crews/CrewTeam.h"
#include "Lab3/departments/StormDepartment.h"
#include "Lab3/messages/CrewComingMessage.h"
#include "Lab3/messages/WorkDoneMessage.h"
#include "Lab3/notifications/ArchivedNotifier.h"
#include "Lab3/notifications/ConsentNotifier.h"
#include "Lab3/notifications/LetterNotifier.h"
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

// The whole text of a file, or an empty text if the file does not exist.
string readFile(const string& fileName) {
    ifstream file(fileName);
    stringstream text;
    text << file.rdbuf();
    return text.str();
}

// ---- Adapter: LetterNotifier adapts the C library (fopen, fputs, fclose) to Notifier ----

void testLetterIsWrittenToTheFile() {
    remove("test_letters.txt");
    LetterNotifier letters("test_letters.txt", "Ion Popescu, 15 Dacia Blvd.");
    Notifier* notifier = &letters;  // used only through the interface, like ReportService does

    startCapture();
    notifier->send("Report #1 was registered.");
    stopCapture();

    check("Adapter: send() puts the home address and the message into the file through the C library",
          readFile("test_letters.txt") == "To: Ion Popescu, 15 Dacia Blvd.\nReport #1 was registered.\n\n");
    remove("test_letters.txt");
}

void testLettersAreAddedAtTheEnd() {
    remove("test_letters.txt");
    LetterNotifier letters("test_letters.txt", "Ion Popescu, 15 Dacia Blvd.");

    startCapture();
    letters.send("First letter.");
    letters.send("Second letter.");
    stopCapture();

    check("Adapter: a second letter is added after the first one, not written over it",
          readFile("test_letters.txt") == "To: Ion Popescu, 15 Dacia Blvd.\nFirst letter.\n\n"
                                          "To: Ion Popescu, 15 Dacia Blvd.\nSecond letter.\n\n");
    remove("test_letters.txt");
}

void testFileThatCannotBeOpenedIsReported() {
    LetterNotifier letters("no_such_folder/test_letters.txt", "Ion Popescu, 15 Dacia Blvd.");

    startCapture();
    letters.send("This letter has nowhere to go.");
    string screen = stopCapture();

    check("Adapter: when fopen returns nullptr, the adapter says the letter could not be written",
          screen.find("could not be written") != string::npos);
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

void testDecoratorWrapsTheAdapter() {
    remove("test_letters.txt");
    LetterNotifier letters("test_letters.txt", "Ion Popescu, 15 Dacia Blvd.");
    SignedNotifier signedLetters(&letters);

    startCapture();
    signedLetters.send("Report #2 was registered.");
    stopCapture();

    check("Decorator: the signature also works around the letter adapter, without changing it",
          readFile("test_letters.txt")
              == "To: Ion Popescu, 15 Dacia Blvd.\nReport #2 was registered. -- Chisinau City Hall\n\n");
    remove("test_letters.txt");
}

// ---- Proxy: ConsentNotifier controls the access to the real notifier ----

void testProxyPassesTheMessageUnchangedWithConsent() {
    RecordingNotifier realNotifier;
    ConsentNotifier proxy(&realNotifier, true);
    Notifier* notifier = &proxy;  // used only through the interface, like ReportService does

    notifier->send("Report #1 was registered.");

    check("Proxy: with consent, the real notifier gets the message exactly as it was sent",
          realNotifier.messages.size() == 1 && realNotifier.messages[0] == "Report #1 was registered.");
}

void testProxyBlocksTheMessageWithoutConsent() {
    RecordingNotifier realNotifier;
    ConsentNotifier proxy(&realNotifier, false);

    startCapture();
    proxy.send("Report #1 was registered.");
    string screen = stopCapture();

    check("Proxy: without consent, the real notifier is never called, and the screen says why",
          realNotifier.messages.empty() && screen.find("not sent") != string::npos);
}

void testProxyStopsTheLetterBeforeTheCLibrary() {
    remove("test_letters.txt");
    LetterNotifier letters("test_letters.txt", "Maria Rusu, 3 Columna St.");
    ConsentNotifier proxy(&letters, false);
    SignedNotifier signedProxy(&proxy);  // the proxy is a Notifier, so a decorator can wrap it

    startCapture();
    signedProxy.send("Report #2 was registered.");
    stopCapture();

    check("Proxy: inside the decorators, a refused letter never reaches fopen, so no file is written",
          readFile("test_letters.txt").empty());
    remove("test_letters.txt");
}

// ---- Bridge: CitizenMessage (what to say) keeps a Notifier (how it travels) ----

// A work order like the ones city hall makes, for the bridge tests.
WorkOrder potholeOrder() {
    WorkOrder order;
    order.reportId = 3;
    order.address = "Ismail St. 40";
    order.deadlineDays = 2;
    return order;
}

void testOneMessageTravelsThroughTwoChannels() {
    ConsoleNotifier console;
    EmailNotifier email;
    WorkDoneMessage byConsole(&console);
    WorkDoneMessage byEmail(&email);

    startCapture();
    byConsole.sendAbout(potholeOrder());
    byEmail.sendAbout(potholeOrder());
    string screen = stopCapture();

    check("Bridge: the same kind of message travels through two different channels",
          screen == "[console] The work at Ismail St. 40 is done. Thank you for report #3.\n"
                    "[e-mail] The work at Ismail St. 40 is done. Thank you for report #3.\n");
}

void testTwoMessagesUseTheSameChannel() {
    RecordingNotifier channel;
    CrewComingMessage crewComing(&channel);
    WorkDoneMessage workDone(&channel);

    crewComing.sendAbout(potholeOrder());
    workDone.sendAbout(potholeOrder());

    check("Bridge: two kinds of message use the same channel, each one with its own text",
          channel.messages.size() == 2
              && channel.messages[0] == "A crew is on its way to Ismail St. 40. The work will be done within 2 days."
              && channel.messages[1] == "The work at Ismail St. 40 is done. Thank you for report #3.");
}

void testCityHallTellsTheCitizenAtEveryStep() {
    ReportStorage storage;
    RecordingNotifier recorder;

    startCapture();
    CityHall cityHall(&storage, &recorder);
    RoadDepartment roads;
    cityHall.addDepartment("Pothole", &roads);
    cityHall.reportProblem("Pothole", "Deep pothole in front of the hospital", "Ismail St. 40", true);
    stopCapture();

    check("Bridge: city hall tells the citizen: registered, then crew on its way, then work done",
          recorder.messages.size() == 3 && recorder.messages[0] == "Report #1 was registered."
              && recorder.messages[1] == "A crew is on its way to Ismail St. 40. The work will be done within 2 days."
              && recorder.messages[2] == "The work at Ismail St. 40 is done. Thank you for report #1.");
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
    CityHall cityHall(&storage, &recorder);
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
    CityHall cityHall(&storage, &console);
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
    CityHall cityHall(&storage, &recorder);
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
    CityHall cityHall(&storage, &recorder);
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
    CityHall cityHall(&storage, &recorder);
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
    testLetterIsWrittenToTheFile();
    testLettersAreAddedAtTheEnd();
    testFileThatCannotBeOpenedIsReported();

    cout << "\n--- Proxy ---\n";
    testProxyPassesTheMessageUnchangedWithConsent();
    testProxyBlocksTheMessageWithoutConsent();
    testProxyStopsTheLetterBeforeTheCLibrary();

    cout << "\n--- Decorator ---\n";
    testSignatureIsAdded();
    testDecoratorsWorkInAnyOrder();
    testDecoratorWrapsTheAdapter();

    cout << "\n--- Bridge ---\n";
    testOneMessageTravelsThroughTwoChannels();
    testTwoMessagesUseTheSameChannel();
    testCityHallTellsTheCitizenAtEveryStep();

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
