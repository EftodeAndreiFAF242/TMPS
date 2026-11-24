// "Capture and restore an object's state without breaking encapsulation"
// Lab 4 - Memento: the Memento, a saved copy of a case that only the case can make and read

#include "Lab4/cases/CaseSnapshot.h"

CaseSnapshot::CaseSnapshot(const ReportState* state, int timesReopened) {
    this->state = state;
    this->timesReopened = timesReopened;
}
