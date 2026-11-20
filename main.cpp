// main.cpp
//
// The start of the program. It shows a menu, and the user picks a laboratory work and how to run it:
// the ready example, where the data is already written in the code,
// or with their own data, typed in the console.
//
// Build and run: see README.md.

#include <ctime>
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

#include "Lab3/calendar/Calendar.h"
#include "Lab3/calendar/SystemCalendar.h"
#include "Lab3/crews/CrewTeam.h"
#include "Lab3/departments/StormDepartment.h"
#include "Lab3/notifications/ArchivedNotifier.h"
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

    // ---- 1. Adapter: the dates of Calendar come from the time functions of the C library ----
    cout << "\n--- 1. Adapter ---\n";

    // The rest of the program knows only Calendar. The adapter turns its one call into the
    // C library's localtime, mktime and strftime.
    SystemCalendar calendar(time(nullptr));
    const Calendar* dates = &calendar;

    cout << "Today is " << dates->dateIn(0) << ".\n";
    cout << "An urgent work order (2 days) must be done by " << dates->dateIn(2) << ".\n";
    cout << "A normal work order (7 days) must be done by " << dates->dateIn(7) << ".\n";
    cout << "In 45 days it is " << dates->dateIn(45) << ": mktime moved the date into the right month.\n";

    // ---- 2. Decorator: notifiers get a signature and an archive, and their code stays the same ----
    cout << "\n--- 2. Decorator ---\n";

    // The archive is a list of its own. ArchivedNotifier only writes into it, so the decorator
    // has nothing more than send(), and main reads the list without knowing who wrote it.
    MessageArchive archive;
    EmailNotifier email;
    SignedNotifier signedEmail(&email);
    ArchivedNotifier archivedEmail(&signedEmail, &archive);

    cout << "The e-mail notifier, wrapped so every message is signed and kept in the archive:\n";
    ReportService decoratedService(&storage, &validator, &archivedEmail);
    decoratedService.submit(Report("Garbage", "The garbage bins on Puskin St. are full"));

    cout << "The same signature works on any notifier, for example on the console:\n";
    ConsoleNotifier console;
    SignedNotifier signedConsole(&console);
    signedConsole.send("The street lights on Ion Creanga St. were repaired.");

    cout << "The archive kept " << archive.all().size() << " message(s):\n";
    for (const string& message : archive.all()) {
        cout << "  - " << message << "\n";
    }

    // ---- 3. Composite: a team of crews is sent out exactly like one crew ----
    cout << "\n--- 3. Composite ---\n";

    // The report is saved straight into the storage here, to show only the crews. Section 4 sends
    // a storm report through city hall, with every check.
    storage.add(Report("Storm damage", "A tree fell across Grenoble St. after the storm"));
    vector<Report> savedReports = storage.all();
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

    // ---- 4. Facade: main only calls reportProblem(), and city hall does every step behind it ----
    cout << "\n--- 4. Facade ---\n";

    // City hall gets the archived and signed e-mail notifier and the calendar adapter, so the
    // patterns work together on every report.
    CityHall cityHall(&storage, &archivedEmail, &calendar);

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

    cout << "\nEvery message city hall sent in this example:\n";
    for (const string& message : archive.all()) {
        cout << "  - " << message << "\n";
    }
}

// Laboratory work 3 with your own data: the reports typed in the console go through city hall.
void runLab3Input(ReportStorage& storage) {
    cout << "\n=== Laboratory work 3: your own reports ===\n";

    ConsoleNotifier consoleNotifier;
    EmailNotifier emailNotifier;
    Notifier* notifier = &consoleNotifier;
    if (ask("How should the citizen be told? 1 - console, 2 - e-mail: ") == "2") {
        notifier = &emailNotifier;
    }

    // Decorator: whatever the channel is, every message is signed and archived.
    MessageArchive archive;
    SignedNotifier signedNotifier(notifier);
    ArchivedNotifier archivedNotifier(&signedNotifier, &archive);

    // Adapter: the dates of the work orders come from the C library, through SystemCalendar.
    SystemCalendar calendar(time(nullptr));

    // Facade: from here on, main only talks to city hall.
    CityHall cityHall(&storage, &archivedNotifier, &calendar);
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
