// "Change an object's behavior when its internal state changes"
// Lab 4 - State: the State, what a case may do in each status

#include "Lab4/statuses/ReportState.h"

// Implicit, niciun pas nu e permis
const ReportState* ReportState::startWork() const {
    return nullptr;
}

const ReportState* ReportState::finishWork() const {
    return nullptr;
}

const ReportState* ReportState::close() const {
    return nullptr;
}

const ReportState* ReportState::reopen() const {
    return nullptr;
}
