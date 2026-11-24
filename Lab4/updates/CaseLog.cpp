// "Notify dependent objects automatically when an object's state changes"
// Lab 4 - Observer: a Concrete Observer, the city hall log of every change, with its date

#include "Lab4/updates/CaseLog.h"

#include <iostream>

#include "Lab3/calendar/Calendar.h"
#include "Lab4/cases/ReportCase.h"

using namespace std;

CaseLog::CaseLog(const Calendar* calendar) {
    this->calendar = calendar;
}

void CaseLog::caseChanged(const ReportCase& reportCase) {
    // Data de azi, apoi starea nouă
    string line = calendar->dateIn(0) + "  report #" + to_string(reportCase.getReportId()) + " ("
                  + reportCase.getCategory() + "): " + reportCase.getStatus();
    lines.push_back(line);
    cout << "[log] " << line << "\n";
}

const vector<string>& CaseLog::entries() const {
    return lines;
}
