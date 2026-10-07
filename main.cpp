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

int main() {
    string choice;

    while (true) {
        cout << "\n===== TMPS laboratory works =====\n";
        cout << "1. Laboratory work 1 - SOLID principles\n";
        cout << "0. Exit\n";
        cout << "Your choice: ";

        // The choice is read as text, not as a number, so typing letters can't break the menu.
        // The reading fails when there is nothing more to read, and then the program stops.
        if (!(cin >> choice)) {
            break;
        }

        if (choice == "1") {
            runLab1();
        } else if (choice == "0") {
            break;
        } else {
            cout << "There is no such option.\n";
        }
    }

    return 0;
}
