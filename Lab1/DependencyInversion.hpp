

//Software entities must depend on abstractions, not on concrete things. 
//Separate modules, that are located on different levels must not depend directly on each other, but should rely on abstractions.



//On screen: How should the citizen be told? 1 - console, 2 - e-mail:
//What proves it: you choose at runtime, and messages start with [console] or [e-mail], but the code of ReportService stays the same.


#pragma once

#include "OpenClosed.hpp"            // for Validator
#include "SingleResponsibility.hpp"  // for Report and ReportStorage

// The abstraction: anything that can deliver a message.
class Notifier {
public:
    virtual ~Notifier() {}
    virtual void send(const string& message) = 0;
};

// Detail 1: writes the message on the screen.
class ConsoleNotifier : public Notifier {
public:
    void send(const string& message) override {
        cout << "[console] " << message << "\n";
    }
};

// Detail 2: pretends to send an e-mail. A real one would talk to a mail server.
class EmailNotifier : public Notifier {
public:
    void send(const string& message) override {
        cout << "[e-mail] " << message << "\n";
    }
};

// High-level code: the steps the application follows when a report comes in.
class ReportService {
public:
    // The service receives what it works with. It does not create anything itself.
    ReportService(ReportStorage* storage, Validator* validator, Notifier* notifier) {
        this->storage = storage;
        this->validator = validator;
        this->notifier = notifier;
    }

    // Handles a new report. Returns true if the report was accepted.
    bool submit(const Report& report) {
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

private:
    ReportStorage* storage;
    Validator* validator;
    Notifier* notifier;  // the interface, never ConsoleNotifier or EmailNotifier
};
