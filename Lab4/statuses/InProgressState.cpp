// "Change an object's behavior when its internal state changes"
// Lab 4 - State: a Concrete State, the crew is working on the problem

#include "Lab4/statuses/InProgressState.h"

#include "Lab4/statuses/FixedState.h"

using namespace std;

string InProgressState::name() const {
    return "In progress";
}

const ReportState* InProgressState::finishWork() const {
    // The crew says it is done
    static const FixedState fixed;
    return &fixed;
}
