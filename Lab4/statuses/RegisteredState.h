// "Change an object's behavior when its internal state changes"
// Lab 4 - State: a Concrete State, the report is saved and waits for a crew

#pragma once

#include <string>

#include "Lab4/statuses/ReportState.h"

// Waiting for a crew to start
class RegisteredState : public ReportState {
public:
    std::string name() const override;
    const ReportState* startWork() const override;
};
