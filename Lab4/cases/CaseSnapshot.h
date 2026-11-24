// "Capture and restore an object's state without breaking encapsulation"
// Lab 4 - Memento: the Memento, a saved copy of a case that only the case can make and read

#pragma once

class ReportState;

// Copia cazului, închisă pentru ceilalți
class CaseSnapshot {
private:
    // Only ReportCase may open it
    friend class ReportCase;

    CaseSnapshot(const ReportState* state, int timesReopened);

    const ReportState* state;
    int timesReopened;
};
