// "Change an object's behavior when its internal state changes"
// Lab 4 - State: a Concrete State, the crew is working on the problem

#pragma once

#include <string>

#include "Lab4/statuses/ReportState.h"

// Echipajul lucrează la problemă
class InProgressState : public ReportState {
public:
    std::string name() const override;
    const ReportState* finishWork() const override;
};
