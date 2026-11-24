// "Notify dependent objects automatically when an object's state changes"
// Lab 4 - Observer: a Concrete Observer, tells the citizen the new status of the report

#pragma once

#include "Lab4/updates/CaseObserver.h"

class Notifier;

// Tells the citizen every new status
class CitizenUpdates : public CaseObserver {
public:
    // Orice notificator, chiar și decorat
    explicit CitizenUpdates(Notifier* notifier);

    void caseChanged(const ReportCase& reportCase) override;

private:
    Notifier* notifier;
};
