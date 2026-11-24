// "Change an object's behavior when its internal state changes"
// Lab 4 - State: a Concrete State, the crew finished and the citizen can check the work

#pragma once

#include <string>

#include "Lab4/statuses/ReportState.h"

// Fixed, waiting for the citizen
class FixedState : public ReportState {
public:
    std::string name() const override;
    const ReportState* close() const override;
    const ReportState* reopen() const override;
};
