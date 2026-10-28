// main.cpp
//
// The start of the program. It shows a menu, and the user picks a laboratory work and how to run it:
// the ready example, where the data is already written in the code,
// or with their own data, typed in the console.
//
// Build:  g++ -I. main.cpp Lab1/*.cpp Lab2/*.cpp -o tmps
// Run:    ./tmps

#include <iostream>
#include <string>
#include <vector>

#include "Lab1/DependencyInversion.h"
#include "Lab1/OpenClosed.h"
#include "Lab1/SingleResponsibility.h"
#include "Lab2/Builder.h"
#include "Lab2/FactoryMethod.h"
#include "Lab2/ObjectPool.h"
#include "Lab2/Singleton.h"

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

void runLab2() {
    cout << "\n=== Laboratory work 2: Creational design patterns ===\n";

    cout << "\n--- 1. Singleton ---\n";

    Database& first = Database::getInstance();
    Database& second = Database::getInstance();

    if (&first == &second) {
        cout << "Both calls returned the same database.\n";
    } else {
        cout << "The calls returned two different databases.\n";
    }

    CategoryRule categoryRule;
    DescriptionRule descriptionRule;
    Validator validator;
    validator.addRule(&categoryRule);
    validator.addRule(&descriptionRule);
    ConsoleNotifier notifier;

    ReportService service(first.getStorage(), &validator, &notifier);
    service.submit(Report("Pothole", "Deep pothole in front of the school"));
    service.submit(Report("Street light", "The street light on the corner is broken"));
    service.submit(Report("Garbage", "Garbage bags left near the park entrance"));

    cout << "The reports were saved through \"first\" and are read through \"second\":\n";
    ReportPrinter printer;
    for (const Report& report : second.getStorage()->all()) {
        printer.print(report);
    }

    cout << "\n--- 2. Builder ---\n";

    vector<Report> reports = Database::getInstance().getStorage()->all();
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

    TruckPool pool(2);
    cout << "City hall has 2 trucks and 3 crews that need one.\n";

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

void runLab2Input() {
    cout << "\n=== Laboratory work 2: your own report ===\n";

    Database& database = Database::getInstance();

    CategoryRule categoryRule;
    DescriptionRule descriptionRule;
    Validator validator;
    validator.addRule(&categoryRule);
    validator.addRule(&descriptionRule);
    ConsoleNotifier notifier;
    ReportService service(database.getStorage(), &validator, &notifier);

    string category = ask("Category (Pothole, Street light, Garbage): ");
    string description = ask("Description (at least 10 characters): ");
    if (!service.submit(Report(category, description))) {
        return;
    }

    vector<Report> reports = database.getStorage()->all();
    const Report& report = reports.back();

    cout << "Every report in the database:\n";
    ReportPrinter printer;
    for (const Report& saved : reports) {
        printer.print(saved);
    }

    string address = ask("\nAddress: ");
    WorkOrderBuilder builder(report, address);

    string priority = ask("Priority (press Enter for Normal): ");
    if (!priority.empty()) {
        builder.setPriority(priority);
    }

    string deadline = ask("Deadline in days (press Enter for 7): ");
    if (!deadline.empty()) {
        try {
            builder.setDeadline(stoi(deadline));
        } catch (...) {
            cout << "That is not a number, so the deadline stays 7 days.\n";
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

int main() {
    string choice;

    while (true) {
        cout << "\n===== TMPS laboratory works =====\n";
        cout << "1. Laboratory work 1 - SOLID principles (ready example)\n";
        cout << "2. Laboratory work 1 - SOLID principles (type your own reports)\n";
        cout << "3. Laboratory work 2 - Creational design patterns (ready example)\n";
        cout << "4. Laboratory work 2 - Creational design patterns (type your own report)\n";
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
            runLab2();
        } else if (choice == "4") {
            runLab2Input();
        } else if (choice == "0") {
            break;
        } else {
            cout << "There is no such option.\n";
        }
    }

    return 0;
}
