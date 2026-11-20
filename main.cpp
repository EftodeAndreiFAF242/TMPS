// main.cpp
//
// The start of the program. It shows a menu, and the user picks a laboratory work and how to run it:
// the ready example, where the data is already written in the code,
// or with their own data, typed in the console.
//
// Build and run: see README.md.

#include <iostream>
#include <memory>
#include <string>
#include <vector>

#include "Lab1/notifications/ConsoleNotifier.h"
#include "Lab1/notifications/EmailNotifier.h"
#include "Lab1/notifications/Notifier.h"
#include "Lab1/reports/Report.h"
#include "Lab1/reports/ReportPrinter.h"
#include "Lab1/reports/ReportService.h"
#include "Lab1/storage/ReportStorage.h"
#include "Lab1/validation/CategoryRule.h"
#include "Lab1/validation/DescriptionRule.h"
#include "Lab1/validation/Validator.h"

#include "Lab2/config/AppConfig.h"
#include "Lab2/crews/ElectricianCrew.h"
#include "Lab2/departments/Department.h"
#include "Lab2/departments/LightingDepartment.h"
#include "Lab2/departments/RoadDepartment.h"
#include "Lab2/departments/SanitationDepartment.h"
#include "Lab2/fleet/Truck.h"
#include "Lab2/fleet/TruckPool.h"
#include "Lab2/workorders/WorkOrder.h"
#include "Lab2/workorders/WorkOrderBuilder.h"
#include "Lab2/workorders/WorkOrderPrinter.h"

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

// Shows a question and returns the line the user types.
// If there is nothing more to read, it returns an empty text.
string ask(string question) {
    cout << question;
    string answer;
    getline(cin, answer);
    return answer;
}

// Laboratory work 1: SOLID principles.
// The three parts use the same objects, so together they are the base of the application.
void runLab1() {
    cout << "\n=== Laboratory work 1: SOLID principles ===\n";

    // ---- 1. Single Responsibility: one class keeps the reports, another one shows them ----
    cout << "\n--- 1. Single Responsibility Principle ---\n";

    ReportStorage storage;
    ReportPrinter printer;

    storage.add(Report("Pothole", "Deep pothole near the bus stop"));
    storage.add(Report("Garbage", "Garbage left next to the playground"));

    for (Report report : storage.all()) {
        printer.print(report);
    }

    // ---- 2. Open/Closed: the validator gets one more rule and its code stays the same ----
    cout << "\n--- 2. Open/Closed Principle ---\n";

    Report badReport("Aliens", "Help");
    CategoryRule categoryRule;
    DescriptionRule descriptionRule;
    Validator validator;

    validator.addRule(&categoryRule);
    cout << "A report with the category \"Aliens\" and the description \"Help\", checked with 1 rule:\n";
    for (string error : validator.validate(badReport)) {
        cout << "  - " << error << "\n";
    }

    validator.addRule(&descriptionRule);
    cout << "The same report, checked with 2 rules:\n";
    for (string error : validator.validate(badReport)) {
        cout << "  - " << error << "\n";
    }

    // ---- 3. Dependency Inversion: the same service works with any notifier ----
    cout << "\n--- 3. Dependency Inversion Principle ---\n";

    ConsoleNotifier consoleNotifier;
    EmailNotifier emailNotifier;

    cout << "The service with the console notifier:\n";
    ReportService service(&storage, &validator, &consoleNotifier);
    service.submit(Report("Street light", "The street light has been off for a week"));
    service.submit(badReport);

    cout << "The same service class with the e-mail notifier:\n";
    ReportService emailService(&storage, &validator, &emailNotifier);
    emailService.submit(Report("Pothole", "The road is broken in front of the school"));

    cout << "\nEvery report in the storage:\n";
    for (Report report : storage.all()) {
        printer.print(report);
    }
}

// Laboratory work 1 with your own data: the same classes, but the reports are typed in the console.
void runLab1Input() {
    cout << "\n=== Laboratory work 1: your own reports ===\n";

    ReportStorage storage;
    CategoryRule categoryRule;
    DescriptionRule descriptionRule;
    Validator validator;
    validator.addRule(&categoryRule);
    validator.addRule(&descriptionRule);

    // Dependency Inversion: the user picks the notifier, and the same service works with either one.
    ConsoleNotifier consoleNotifier;
    EmailNotifier emailNotifier;
    Notifier* notifier = &consoleNotifier;
    if (ask("How should the citizen be told? 1 - console, 2 - e-mail: ") == "2") {
        notifier = &emailNotifier;
    }
    ReportService service(&storage, &validator, notifier);

    // Open/Closed: every report goes through the rules of the validator.
    cout << "Known categories: Pothole, Street light, Garbage. A description needs at least 10 characters.\n";
    while (true) {
        string category = ask("\nCategory (or press Enter to stop): ");
        if (category == "") {
            break;
        }
        string description = ask("Description: ");
        service.submit(Report(category, description));
    }

    // Single Responsibility: the storage kept the reports, and the printer shows them.
    cout << "\nEvery report in the storage:\n";
    ReportPrinter printer;
    for (Report report : storage.all()) {
        printer.print(report);
    }
}

// Laboratory work 2: creational design patterns.
// The reports are saved in the storage that main() made, so they stay there between runs.
void runLab2(ReportStorage& storage) {
    cout << "\n=== Laboratory work 2: Creational design patterns ===\n";

    cout << "\n--- 1. Singleton ---\n";

    const AppConfig& first = AppConfig::getInstance();
    const AppConfig& second = AppConfig::getInstance();

    if (&first == &second) {
        cout << "Both calls returned the same settings.\n";
    } else {
        cout << "The calls returned two different settings.\n";
    }

    cout << "The settings of the application:\n";
    cout << "  default priority: " << first.getDefaultPriority() << "\n";
    cout << "  default deadline: " << first.getDefaultDeadlineDays() << " days\n";
    cout << "  trucks:           " << first.getTruckCount() << "\n";

    cout << "\n--- 2. Builder ---\n";

    CategoryRule categoryRule;
    DescriptionRule descriptionRule;
    Validator validator;
    validator.addRule(&categoryRule);
    validator.addRule(&descriptionRule);
    ConsoleNotifier notifier;

    ReportService service(&storage, &validator, &notifier);
    service.submit(Report("Pothole", "Deep pothole in front of the school"));
    service.submit(Report("Street light", "The street light on the corner is broken"));
    service.submit(Report("Garbage", "Garbage bags left near the park entrance"));

    vector<Report> reports = storage.all();
    size_t last = reports.size() - 1;

    WorkOrder potholeOrder = WorkOrderBuilder(reports[last - 2], "Stefan cel Mare Blvd. 12")
                                 .setPriority("High")
                                 .setDeadline(2)
                                 .setNote("Children cross here, put up a warning sign first")
                                 .build();

    WorkOrder lightOrder = WorkOrderBuilder(reports[last - 1], "Dacia Blvd. 5")
                               .setDeadline(3)
                               .build();

    WorkOrder garbageOrder = WorkOrderBuilder(reports[last], "Valea Morilor park").build();

    WorkOrderPrinter orderPrinter;
    orderPrinter.print(potholeOrder);
    orderPrinter.print(lightOrder);
    orderPrinter.print(garbageOrder);

    cout << "\n--- 3. Factory Method ---\n";

    RoadDepartment roads;
    LightingDepartment lighting;
    SanitationDepartment sanitation;

    roads.handle(potholeOrder);
    lighting.handle(lightOrder);
    sanitation.handle(garbageOrder);

    cout << "\n--- 4. Object Pool (extra) ---\n";

    // The number of trucks comes from the settings. "second" is the same object as "first".
    int truckCount = second.getTruckCount();
    TruckPool pool(truckCount);
    cout << "City hall has " << truckCount << " trucks and 3 crews that need one.\n";

    Truck* roadTruck = pool.acquire();
    cout << "The road crew takes truck #" << roadTruck->number << ".\n";

    Truck* lightTruck = pool.acquire();
    cout << "The electricians take truck #" << lightTruck->number << ".\n";

    Truck* garbageTruck = pool.acquire();
    if (garbageTruck == nullptr) {
        cout << "No truck is free, so the garbage crew waits.\n";
    }

    cout << "The road crew is done and gives truck #" << roadTruck->number << " back.\n";
    pool.release(roadTruck);

    garbageTruck = pool.acquire();
    cout << "The garbage crew takes truck #" << garbageTruck->number
         << ". It is the same truck, it was not made again.\n";
}

// Laboratory work 2 with your own data: one report typed in the console goes all the way through.
void runLab2Input(ReportStorage& storage) {
    cout << "\n=== Laboratory work 2: your own report ===\n";

    const AppConfig& config = AppConfig::getInstance();

    CategoryRule categoryRule;
    DescriptionRule descriptionRule;
    Validator validator;
    validator.addRule(&categoryRule);
    validator.addRule(&descriptionRule);
    ConsoleNotifier notifier;
    ReportService service(&storage, &validator, &notifier);

    string category = ask("Category (Pothole, Street light, Garbage): ");
    string description = ask("Description (at least 10 characters): ");
    if (!service.submit(Report(category, description))) {
        return;
    }

    vector<Report> reports = storage.all();
    const Report& report = reports.back();

    cout << "Every report in the storage:\n";
    ReportPrinter printer;
    for (const Report& saved : reports) {
        printer.print(saved);
    }

    string address = ask("\nAddress: ");
    WorkOrderBuilder builder(report, address);

    string priority = ask("Priority (press Enter for " + config.getDefaultPriority() + "): ");
    if (!priority.empty()) {
        builder.setPriority(priority);
    }

    string defaultDeadline = to_string(config.getDefaultDeadlineDays());
    string deadline = ask("Deadline in days (press Enter for " + defaultDeadline + "): ");
    if (!deadline.empty()) {
        try {
            builder.setDeadline(stoi(deadline));
        } catch (...) {
            cout << "That is not a number, so the deadline stays " << defaultDeadline << " days.\n";
        }
    }

    string note = ask("Note (press Enter for none): ");
    if (!note.empty()) {
        builder.setNote(note);
    }

    WorkOrder order = builder.build();
    WorkOrderPrinter orderPrinter;
    orderPrinter.print(order);

    RoadDepartment roads;
    LightingDepartment lighting;
    SanitationDepartment sanitation;
    const Department* department = &roads;
    if (category == "Street light") {
        department = &lighting;
    } else if (category == "Garbage") {
        department = &sanitation;
    }
    department->handle(order);
}

// Laboratory work 3: structural design patterns.
// The reports are saved in the same storage as in lab 2, because it is one system.
void runLab3(ReportStorage& storage) {
    cout << "\n=== Laboratory work 3: Structural design patterns ===\n";

    CategoryRule categoryRule;
    DescriptionRule descriptionRule;
    Validator validator;
    validator.addRule(&categoryRule);
    validator.addRule(&descriptionRule);

    // ---- 1. Adapter: ReportService from lab 1 writes paper letters through the C library ----
    cout << "\n--- 1. Adapter ---\n";

    LetterNotifier letters("letters.txt", "Ion Popescu, 15 Dacia Blvd.");

    cout << "ReportService from lab 1 gets a LetterNotifier, and its code stays the same:\n";
    ReportService letterService(&storage, &validator, &letters);
    letterService.submit(Report("Street light", "Three street lights are off on Ion Creanga St."));
    letterService.submit(Report("Pothole", "Hole"));

    cout << "A file that can't be opened makes fopen return nullptr, and the adapter says so:\n";
    LetterNotifier noFolder("no_such_folder/letters.txt", "Ion Popescu, 15 Dacia Blvd.");
    noFolder.send("This letter has nowhere to go.");

    // ---- 2. Proxy: a stand-in that lets a letter through only if the citizen agreed ----
    cout << "\n--- 2. Proxy ---\n";

    // Each proxy stands in front of a real letter notifier, and ReportService from lab 1 gets the
    // proxy as a Notifier, so it does not know that the access is checked.
    ConsentNotifier lettersToIon(&letters, true);
    LetterNotifier mariasLetters("letters.txt", "Maria Rusu, 3 Columna St.");
    ConsentNotifier lettersToMaria(&mariasLetters, false);

    cout << "Ion agreed to get letters, so the proxy passes the message on unchanged:\n";
    ReportService ionService(&storage, &validator, &lettersToIon);
    ionService.submit(Report("Garbage", "Garbage bags left behind the school on Columna St."));

    cout << "Maria did not agree, so the proxy stops the letter before it reaches the C library:\n";
    ReportService mariaService(&storage, &validator, &lettersToMaria);
    mariaService.submit(Report("Pothole", "A deep pothole in front of 3 Columna St."));

    // ---- 3. Decorator: notifiers get a signature and an archive, and their code stays the same ----
    cout << "\n--- 3. Decorator ---\n";

    // The archive is a list of its own. ArchivedNotifier only writes into it, so the decorator
    // has nothing more than send(), and main reads the list without knowing who wrote it.
    MessageArchive archive;
    SignedNotifier signedLetters(&lettersToIon);
    ArchivedNotifier archivedLetters(&signedLetters, &archive);

    cout << "Ion's letters (through the proxy), wrapped so every message is signed and archived:\n";
    ReportService decoratedService(&storage, &validator, &archivedLetters);
    decoratedService.submit(Report("Garbage", "The garbage bins on Puskin St. are full"));

    cout << "The same signature works on any notifier, for example on e-mail:\n";
    EmailNotifier email;
    SignedNotifier signedEmail(&email);
    signedEmail.send("The street lights on Ion Creanga St. were repaired.");

    cout << "The archive kept " << archive.all().size() << " message(s):\n";
    for (const string& message : archive.all()) {
        cout << "  - " << message << "\n";
    }

    // ---- 4. Bridge: what city hall says and how it travels are two separate hierarchies ----
    cout << "\n--- 4. Bridge ---\n";

    // A work order for the garbage report that was just registered.
    vector<Report> savedReports = storage.all();
    WorkOrder garbageOrder = WorkOrderBuilder(savedReports.back(), "Puskin St. 22").build();

    cout << "The same message, \"the work is done\", through two different channels:\n";
    WorkDoneMessage doneByEmail(&email);
    WorkDoneMessage doneByLetter(&archivedLetters);
    doneByEmail.sendAbout(garbageOrder);
    doneByLetter.sendAbout(garbageOrder);

    cout << "Two different messages through the same channel:\n";
    CrewComingMessage comingByEmail(&email);
    comingByEmail.sendAbout(garbageOrder);
    doneByEmail.sendAbout(garbageOrder);

    // ---- 5. Composite: a team of crews is sent out exactly like one crew ----
    cout << "\n--- 5. Composite ---\n";

    // The report is saved straight into the storage here, to show only the crews. Section 6 sends
    // a storm report through city hall, with every check.
    storage.add(Report("Storm damage", "A tree fell across Grenoble St. after the storm"));
    savedReports = storage.all();
    WorkOrder stormOrder = WorkOrderBuilder(savedReports.back(), "Grenoble St. 120")
                               .setPriority("High")
                               .build();

    cout << "A department of lab 2 sends one crew:\n";
    RoadDepartment roadDepartment;
    roadDepartment.handle(stormOrder);

    cout << "The storm department sends a team, through the same handle() of lab 2:\n";
    StormDepartment stormDepartment;
    stormDepartment.handle(stormOrder);

    cout << "A team can have another team inside it, for a really big job:\n";
    CrewTeam bigTeam;
    bigTeam.add(make_unique<ElectricianCrew>());
    bigTeam.add(stormDepartment.createCrew());
    bigTeam.work(stormOrder);

    // ---- 6. Facade: main only calls reportProblem(), and city hall does every step behind it ----
    cout << "\n--- 6. Facade ---\n";

    // City hall gets the archived and signed notifier, which goes through the consent proxy to the
    // letter adapter, so the patterns work together on every report.
    CityHall cityHall(&storage, &archivedLetters);

    // main tells city hall which department takes care of which category. A new department is
    // one more class and one more line here, and the code of CityHall does not change.
    RoadDepartment roads;
    LightingDepartment lighting;
    SanitationDepartment sanitation;
    cityHall.addDepartment("Pothole", &roads);
    cityHall.addDepartment("Street light", &lighting);
    cityHall.addDepartment("Garbage", &sanitation);
    cityHall.addDepartment("Storm damage", &stormDepartment);

    cout << "An urgent pothole, reported with one call:\n";
    cityHall.reportProblem("Pothole", "Deep pothole in front of the hospital", "Ismail St. 40", true);

    cout << "\nA broken street light that is not urgent:\n";
    cityHall.reportProblem("Street light", "The street light near the school is blinking",
                           "Mihai Viteazul St. 7", false);

    cout << "\nStorm damage: a new category, and its department sends a team (Composite):\n";
    cityHall.reportProblem("Storm damage", "A tree fell across Grenoble St. after the storm",
                           "Grenoble St. 120", true);

    cout << "\nA report that is refused does not get a work order:\n";
    cityHall.reportProblem("Aliens", "Help", "Nowhere", false);

    cout << "\nEvery letter city hall sent in this example:\n";
    for (const string& message : archive.all()) {
        cout << "  - " << message << "\n";
    }
    cout << "The letters are in the file letters.txt, ready for the post office.\n";
}

// Laboratory work 3 with your own data: the reports typed in the console go through city hall.
void runLab3Input(ReportStorage& storage) {
    cout << "\n=== Laboratory work 3: your own reports ===\n";

    // Adapter: a paper letter is one more way to tell the citizen.
    ConsoleNotifier consoleNotifier;
    EmailNotifier emailNotifier;

    string channel = ask("How should the citizen be told? 1 - console, 2 - e-mail, 3 - paper letter: ");
    string homeAddress;
    bool agreed = true;
    if (channel == "3") {
        homeAddress = ask("The citizen's home address: ");
        agreed = ask("Did the citizen agree to get letters? (y/n): ") == "y";
    }
    LetterNotifier letterNotifier("letters.txt", homeAddress);

    // Proxy: the letters go through the consent check before they reach the adapter.
    ConsentNotifier consentLetters(&letterNotifier, agreed);

    Notifier* notifier = &consoleNotifier;
    if (channel == "2") {
        notifier = &emailNotifier;
    } else if (channel == "3") {
        notifier = &consentLetters;
    }

    // Decorator: whatever the channel is, every message is signed and archived.
    MessageArchive archive;
    SignedNotifier signedNotifier(notifier);
    ArchivedNotifier archivedNotifier(&signedNotifier, &archive);

    // Facade: from here on, main only talks to city hall.
    CityHall cityHall(&storage, &archivedNotifier);
    RoadDepartment roads;
    LightingDepartment lighting;
    SanitationDepartment sanitation;
    cityHall.addDepartment("Pothole", &roads);
    cityHall.addDepartment("Street light", &lighting);
    cityHall.addDepartment("Garbage", &sanitation);
    StormDepartment storm;
    cityHall.addDepartment("Storm damage", &storm);

    cout << "Known categories: Pothole, Street light, Garbage, Storm damage. "
            "A description needs at least 10 characters.\n";
    while (true) {
        string category = ask("\nCategory (or press Enter to stop): ");
        if (category == "") {
            break;
        }
        string description = ask("Description: ");
        string address = ask("Address: ");
        bool urgent = ask("Is it urgent? (y/n): ") == "y";
        cityHall.reportProblem(category, description, address, urgent);
    }

    cout << "\nEvery message city hall sent:\n";
    for (const string& message : archive.all()) {
        cout << "  - " << message << "\n";
    }
}

int main() {
    // The reports of labs 2 and 3 are kept here for the whole run of the program. main() makes
    // the storage once and gives it to the code that needs it, so it does not have to be a singleton.
    ReportStorage storage;
    string choice;

    while (true) {
        cout << "\n===== TMPS laboratory works =====\n";
        cout << "1. Laboratory work 1 - SOLID principles (ready example)\n";
        cout << "2. Laboratory work 1 - SOLID principles (type your own reports)\n";
        cout << "3. Laboratory work 2 - Creational design patterns (ready example)\n";
        cout << "4. Laboratory work 2 - Creational design patterns (type your own report)\n";
        cout << "5. Laboratory work 3 - Structural design patterns (ready example)\n";
        cout << "6. Laboratory work 3 - Structural design patterns (type your own reports)\n";
        cout << "0. Exit\n";
        cout << "Your choice: ";

        // The whole line is read as text, not as a number, so typing letters can't break the menu.
        // The reading fails when there is nothing more to read, and then the program stops.
        if (!getline(cin, choice)) {
            break;
        }

        if (choice == "1") {
            runLab1();
        } else if (choice == "2") {
            runLab1Input();
        } else if (choice == "3") {
            runLab2(storage);
        } else if (choice == "4") {
            runLab2Input(storage);
        } else if (choice == "5") {
            runLab3(storage);
        } else if (choice == "6") {
            runLab3Input(storage);
        } else if (choice == "0") {
            break;
        } else {
            cout << "There is no such option.\n";
        }
    }

    return 0;
}
