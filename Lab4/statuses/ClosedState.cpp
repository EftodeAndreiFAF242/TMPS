// "Change an object's behavior when its internal state changes"
// Lab 4 - State: a Concrete State, the case is over and refuses every step

#include "Lab4/statuses/ClosedState.h"

using namespace std;

string ClosedState::name() const {
    return "Closed";
}
