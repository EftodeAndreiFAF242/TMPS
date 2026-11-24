// "Change an object's behavior when its internal state changes"
// Lab 4 - State: the State, what a case may do in each status

#pragma once

#include <string>

// Fiecare stare știe ce urmează
class ReportState {
public:
    virtual ~ReportState() {}

    // The status the citizen sees
    virtual std::string name() const = 0;

    // Next state, or nullptr if forbidden
    virtual const ReportState* startWork() const;
    virtual const ReportState* finishWork() const;
    virtual const ReportState* close() const;
    virtual const ReportState* reopen() const;
};
