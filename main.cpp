// main.cpp
//
// The start of the program. It shows a menu, the user picks a laboratory work,
// and the demo of that laboratory work runs.
//
// Build:  g++ main.cpp -o tmps
// Run:    ./tmps

#include "Lab1/SingleResponsibility.hpp"
#include "Lab1/OpenClosed.hpp"
#include "Lab1/DependencyInversion.hpp"
#include "Lab2/Singleton.hpp"
#include "Lab2/Builder.hpp"
#include "Lab2/FactoryMethod.hpp"
#include "Lab2/ObjectPool.hpp"

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

// Laboratory work 2: creational design patterns.
// It continues lab 1: the reports go into the one database, each report becomes a work order,
// and a department sends a crew to do the job.
void runLab2() {
    cout << "\n=== Laboratory work 2: Creational design patterns ===\n";

    // ---- 1. Singleton: the whole program uses the same database ----
    cout << "\n--- 1. Singleton ---\n";

    Database& first = Database::getInstance();   // the first call makes the database
    Database& second = Database::getInstance();  // the second call makes nothing, it gets the same one

    // Two names for one object have the same address in memory.
    if (&first == &second) {
        cout << "Both calls returned the same database.\n";
    } else {
        cout << "The calls returned two different databases.\n";
    }

    // The service from lab 1 still gets its storage from outside. Now it is the database's storage.
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
    for (Report report : second.getStorage()->all()) {
        printer.print(report);
    }

    // ---- 2. Builder: work orders with only the parts each one needs ----
    cout << "\n--- 2. Builder ---\n";

    // Any part of the program can ask for the database and gets the same reports.
    vector<Report> reports = Database::getInstance().getStorage()->all();

    // Every optional part is given.
    WorkOrder potholeOrder = WorkOrderBuilder(reports[0], "Stefan cel Mare Blvd. 12")
                                 .setPriority("High")
                                 .setDeadline(2)
                                 .setNote("Children cross here, put up a warning sign first")
                                 .build();

    // Only the deadline is given. The priority keeps its default value.
    WorkOrder lightOrder = WorkOrderBuilder(reports[1], "Dacia Blvd. 5")
                               .setDeadline(3)
                               .build();

    // No optional part is given. Everything else keeps the default values.
    WorkOrder garbageOrder = WorkOrderBuilder(reports[2], "Valea Morilor park").build();

    WorkOrderPrinter orderPrinter;
    orderPrinter.print(potholeOrder);
    orderPrinter.print(lightOrder);
    orderPrinter.print(garbageOrder);

    // ---- 3. Factory Method: each department makes its own kind of crew ----
    cout << "\n--- 3. Factory Method ---\n";

    RoadDepartment roads;
    LightingDepartment lighting;
    SanitationDepartment sanitation;

    // handle() is the same code for all three. Only the crew that createCrew() makes is different.
    roads.handle(potholeOrder);
    lighting.handle(lightOrder);
    sanitation.handle(garbageOrder);

    // ---- 4. Object Pool (extra): the crews share a few trucks ----
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

int main() {
    string choice;

    while (true) {
        cout << "\n===== TMPS laboratory works =====\n";
        cout << "1. Laboratory work 1 - SOLID principles\n";
        cout << "2. Laboratory work 2 - Creational design patterns\n";
        cout << "0. Exit\n";
        cout << "Your choice: ";

        // The choice is read as text, not as a number, so typing letters can't break the menu.
        // The reading fails when there is nothing more to read, and then the program stops.
        if (!(cin >> choice)) {
            break;
        }

        if (choice == "1") {
            runLab1();
        } else if (choice == "2") {
            runLab2();
        } else if (choice == "0") {
            break;
        } else {
            cout << "There is no such option.\n";
        }
    }

    return 0;
}
