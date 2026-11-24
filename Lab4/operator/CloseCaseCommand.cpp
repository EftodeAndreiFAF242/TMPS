// "Turn a request into an object so it can be queued, logged or undone"
// Lab 4 - Command: a Concrete Command, the citizen confirmed, so the case is closed

#include "Lab4/operator/CloseCaseCommand.h"

#include "Lab4/cases/ReportCase.h"

using namespace std;

CloseCaseCommand::CloseCaseCommand(ReportCase* reportCase)
    : reportCase(reportCase), before(reportCase->save()) {}

string CloseCaseCommand::name() const {
    return "close the case of report #" + to_string(reportCase->getReportId());
}

string CloseCaseCommand::execute() {
    // Remember the case, then ask it
    before = reportCase->save();
    return reportCase->close();
}

void CloseCaseCommand::undo() {
    reportCase->restore(before);
}
