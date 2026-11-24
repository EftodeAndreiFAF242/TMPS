// "Turn a request into an object so it can be queued, logged or undone"
// Lab 4 - Command: a Concrete Command, the crew starts the work on a case

#include "Lab4/operator/StartWorkCommand.h"

#include "Lab4/cases/ReportCase.h"

using namespace std;

StartWorkCommand::StartWorkCommand(ReportCase* reportCase)
    : reportCase(reportCase), before(reportCase->save()) {}

string StartWorkCommand::name() const {
    return "start the work on report #" + to_string(reportCase->getReportId());
}

string StartWorkCommand::execute() {
    // Remember the case, then ask it
    before = reportCase->save();
    return reportCase->startWork();
}

void StartWorkCommand::undo() {
    reportCase->restore(before);
}
