// "Turn a request into an object so it can be queued, logged or undone"
// Lab 4 - Command: a Concrete Command, the crew starts the work on a case

#pragma once

#include <string>

#include "Lab4/cases/CaseSnapshot.h"
#include "Lab4/operator/Command.h"

class ReportCase;

// Echipajul începe lucrul
class StartWorkCommand : public Command {
public:
    explicit StartWorkCommand(ReportCase* reportCase);

    std::string name() const override;
    std::string execute() override;
    void undo() override;

private:
    ReportCase* reportCase;  // the Receiver, does the work
    CaseSnapshot before;     // copia pentru anulare
};
