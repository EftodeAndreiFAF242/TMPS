// "Notify dependent objects automatically when an object's state changes"
// Lab 4 - Observer: a Concrete Observer, the city hall log of every change, with its date

#pragma once

#include <string>
#include <vector>

#include "Lab4/updates/CaseObserver.h"

class Calendar;

// Jurnalul primăriei, cu data
class CaseLog : public CaseObserver {
public:
    // Dates from lab 3's adapter
    explicit CaseLog(const Calendar* calendar);

    void caseChanged(const ReportCase& reportCase) override;

    // Every line, in order
    const std::vector<std::string>& entries() const;

private:
    const Calendar* calendar;
    std::vector<std::string> lines;
};
