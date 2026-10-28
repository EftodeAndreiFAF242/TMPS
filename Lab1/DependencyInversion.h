//Software entities must depend on abstractions, not on concrete things.
//Separate modules, that are located on different levels must not depend directly on each other, but should rely on abstractions.



//On screen: How should the citizen be told? 1 - console, 2 - e-mail:
//What proves it: you choose at runtime, and messages start with [console] or [e-mail], but the code of ReportService stays the same.


#pragma once

#include <string>

struct Report;
class ReportStorage;
class Validator;

// The abstraction: anything that can deliver a message.
class Notifier {
public:
    virtual ~Notifier() {}
    virtual void send(const std::string& message) = 0;
};

// Detail 1: writes the message on the screen.
class ConsoleNotifier : public Notifier {
public:
    void send(const std::string& message) override;
};

// Detail 2: pretends to send an e-mail. A real one would talk to a mail server.
class EmailNotifier : public Notifier {
public:
    void send(const std::string& message) override;
};

// High-level code: the steps the application follows when a report comes in.
class ReportService {
public:
    // The service receives what it works with. It does not create anything itself.
    ReportService(ReportStorage* storage, Validator* validator, Notifier* notifier);

    // Handles a new report. Returns true if the report was accepted.
    bool submit(const Report& report);

private:
    ReportStorage* storage;
    Validator* validator;
    Notifier* notifier;  // the interface, never ConsoleNotifier or EmailNotifier
};
