// "Change an object's behavior when its internal state changes"
// Lab 4 - State: a Concrete State, the report is saved and waits for a crew

#include "Lab4/statuses/RegisteredState.h"

#include "Lab4/statuses/InProgressState.h"

using namespace std;

string RegisteredState::name() const {
    return "Registered";
}

const ReportState* RegisteredState::startWork() const {
    // One shared object is enough
    static const InProgressState inProgress;
    return &inProgress;
}
