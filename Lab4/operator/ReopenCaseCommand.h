// "Turn a request into an object so it can be queued, logged or undone"
// Lab 4 - Command: a Concrete Command, the problem is still there, so the case is reopened

#pragma once

#include <string>

#include "Lab4/cases/CaseSnapshot.h"
#include "Lab4/operator/Command.h"

class ReportCase;

// The problem is still there
class ReopenCaseCommand : public Command {
public:
    explicit ReopenCaseCommand(ReportCase* reportCase);

    std::string name() const override;
    std::string execute() override;
    void undo() override;

private:
    ReportCase* reportCase;  // the Receiver, does the work
    CaseSnapshot before;     // copia pentru anulare
};
