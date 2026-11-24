// "Turn a request into an object so it can be queued, logged or undone"
// Lab 4 - Command: a Concrete Command, the problem is still there, so the case is reopened

#include "Lab4/operator/ReopenCaseCommand.h"

#include "Lab4/cases/ReportCase.h"

using namespace std;

ReopenCaseCommand::ReopenCaseCommand(ReportCase* reportCase)
    : reportCase(reportCase), before(reportCase->save()) {}

string ReopenCaseCommand::name() const {
    return "reopen the case of report #" + to_string(reportCase->getReportId());
}

string ReopenCaseCommand::execute() {
    // Întâi copia, apoi pasul
    before = reportCase->save();
    return reportCase->reopen();
}

void ReopenCaseCommand::undo() {
    reportCase->restore(before);
}
