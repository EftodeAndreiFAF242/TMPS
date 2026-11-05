// Lab 1 - Dependency Inversion Principle (DIP): the high-level module, it knows only the Notifier interface

#include "Lab1/reports/ReportService.h"

#include <string>
#include <vector>

#include "Lab1/notifications/Notifier.h"
#include "Lab1/reports/Report.h"
#include "Lab1/storage/ReportStorage.h"
#include "Lab1/validation/Validator.h"

using namespace std;

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
