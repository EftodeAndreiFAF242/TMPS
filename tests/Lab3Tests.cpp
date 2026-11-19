// Lab 3 - Unit tests: at least two tests for each structural pattern, each one proves its key property

#include <cstdio>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "Lab1/notifications/ConsoleNotifier.h"
#include "Lab1/notifications/Notifier.h"
#include "Lab1/storage/ReportStorage.h"
#include "Lab2/departments/LightingDepartment.h"
#include "Lab2/departments/RoadDepartment.h"
#include "Lab3/notifications/ArchivedNotifier.h"
#include "Lab3/notifications/LetterNotifier.h"
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
    SignedNotifier signed1(&recorder1);
    ArchivedNotifier archiveOutside(&signed1);
    archiveOutside.send("Hello");

    // Order 2: the signature is outside the archive, so the archive keeps the signed text.
    RecordingNotifier recorder2;
    ArchivedNotifier archiveInside(&recorder2);
    SignedNotifier signed2(&archiveInside);
    signed2.send("Hello");

    check("Decorator: in both orders the citizen gets the signed message",
          recorder1.messages.size() == 1 && recorder1.messages[0] == "Hello -- Chisinau City Hall"
              && recorder2.messages.size() == 1 && recorder2.messages[0] == "Hello -- Chisinau City Hall");
    check("Decorator: the order of the decorators decides what the archive keeps",
          archiveOutside.getHistory().size() == 1 && archiveOutside.getHistory()[0] == "Hello"
              && archiveInside.getHistory().size() == 1
              && archiveInside.getHistory()[0] == "Hello -- Chisinau City Hall");
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

int main() {
    cout << "=== Unit tests of laboratory work 3: structural design patterns ===\n";

    cout << "\n--- Adapter ---\n";
    testLetterIsWrittenToTheFile();
    testLettersAreAddedAtTheEnd();
    testFileThatCannotBeOpenedIsReported();

    cout << "\n--- Decorator ---\n";
    testSignatureIsAdded();
    testDecoratorsWorkInAnyOrder();
    testDecoratorWrapsTheAdapter();

    cout << "\n--- Facade ---\n";
    testAcceptedReportGoesThroughEveryStepInOrder();
    testRefusedReportGetsNoWorkOrder();
    testEachCategoryGoesToItsDepartment();

    cout << "\n" << testsRun << " tests, " << testsRun - testsFailed << " passed, " << testsFailed
         << " failed.\n";
    return testsFailed;
}
