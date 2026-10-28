#include "Lab1/DependencyInversion.h"

#include <iostream>
#include <vector>

#include "Lab1/OpenClosed.h"
#include "Lab1/SingleResponsibility.h"

using namespace std;

void ConsoleNotifier::send(const string& message) {
    cout << "[console] " << message << "\n";
}

void EmailNotifier::send(const string& message) {
    cout << "[e-mail] " << message << "\n";
}

ReportService::ReportService(ReportStorage* storage, Validator* validator, Notifier* notifier) {
    this->storage = storage;
    this->validator = validator;
    this->notifier = notifier;
}

bool ReportService::submit(const Report& report) {
    // Step 1: check the report. A report with errors is not saved.
    vector<string> errors = validator->validate(report);
    if (!errors.empty()) {
        for (string error : errors) {
            notifier->send("Report refused: " + error);
        }
        return false;
    }

    // Step 2: save it.
    int id = storage->add(report);

    // Step 3: tell the citizen. The service does not know how the message travels.
    notifier->send("Report #" + to_string(id) + " was registered.");
    return true;
}
