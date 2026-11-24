// "Turn a request into an object so it can be queued, logged or undone"
// Lab 4 - Command: a Concrete Command, the crew says the work is done

#include "Lab4/operator/FinishWorkCommand.h"

#include "Lab4/cases/ReportCase.h"

using namespace std;

FinishWorkCommand::FinishWorkCommand(ReportCase* reportCase)
    : reportCase(reportCase), before(reportCase->save()) {}

string FinishWorkCommand::name() const {
    return "finish the work on report #" + to_string(reportCase->getReportId());
}

string FinishWorkCommand::execute() {
    // Întâi copia, apoi pasul
    before = reportCase->save();
    return reportCase->finishWork();
}

void FinishWorkCommand::undo() {
    reportCase->restore(before);
}
