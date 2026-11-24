// "Notify dependent objects automatically when an object's state changes"
// Lab 4 - Observer: the Observer, anyone who wants to hear when a case changes

#pragma once

class ReportCase;

// Aude când cazul se schimbă
class CaseObserver {
public:
    virtual ~CaseObserver() {}
    virtual void caseChanged(const ReportCase& reportCase) = 0;
};
