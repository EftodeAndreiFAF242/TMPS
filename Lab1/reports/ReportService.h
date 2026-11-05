// Lab 1 - Dependency Inversion Principle (DIP): the high-level module, it knows only the Notifier interface

#pragma once

struct Report;
class Notifier;
class ReportStorage;
class Validator;

// Takes in a new report: checks it, saves it and tells the citizen what happened.
class ReportService {
public:
    // The service receives what it works with. It does not create anything itself.
    ReportService(ReportStorage* storage, Validator* validator, Notifier* notifier);

    // Handles a new report. Returns true if the report was accepted.
    bool submit(const Report& report);

private:
    ReportStorage* storage;
    Validator* validator;
    Notifier* notifier;  // any notifier: the service never knows if it is the console or e-mail
};
