// "Change an object's behavior when its internal state changes"
// Lab 4 - State: a Concrete State, the case is over and refuses every step

#pragma once

#include <string>

#include "Lab4/statuses/ReportState.h"

// Closed: no step is allowed
class ClosedState : public ReportState {
public:
    std::string name() const override;
};
