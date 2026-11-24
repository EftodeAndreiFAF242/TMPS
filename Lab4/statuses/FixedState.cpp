// "Change an object's behavior when its internal state changes"
// Lab 4 - State: a Concrete State, the crew finished and the citizen can check the work

#include "Lab4/statuses/FixedState.h"

#include "Lab4/statuses/ClosedState.h"
#include "Lab4/statuses/InProgressState.h"

using namespace std;

string FixedState::name() const {
    return "Fixed";
}

const ReportState* FixedState::close() const {
    // Cetățeanul confirmă, cazul se închide
    static const ClosedState closed;
    return &closed;
}

const ReportState* FixedState::reopen() const {
    // Still broken, back to work
    static const InProgressState inProgress;
    return &inProgress;
}
