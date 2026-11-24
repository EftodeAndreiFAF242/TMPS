// "Change an object's behavior when its internal state changes"
// Lab 4 - State: the Context, the case of one report, followed until it is closed (and the Subject of Observer)

#pragma once

#include <string>
#include <vector>

struct Report;
class CaseObserver;
class ReportState;

// Cazul unei sesizări, până la capăt
class ReportCase {
public:
    explicit ReportCase(const Report& report);

    // Empty text = done, else why not
    std::string startWork();
    std::string finishWork();
    std::string close();
    std::string reopen();

    // Who hears about every change
    void subscribe(CaseObserver* observer);
    void unsubscribe(CaseObserver* observer);

    int getReportId() const;
    const std::string& getCategory() const;
    std::string getStatus() const;
    int getTimesReopened() const;

private:
    // Moves only if the state allows
    std::string moveTo(const ReportState* next, const std::string& step);
    void notifyObservers() const;

    int reportId;
    std::string category;
    const ReportState* state;  // obiect comun, nu se șterge
    int timesReopened;
    std::vector<CaseObserver*> observers;
};
