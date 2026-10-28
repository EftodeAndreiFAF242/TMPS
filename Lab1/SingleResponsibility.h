//Every piece of software (i.e. module, class or function) should be responsible over a single part of functionality provided by the software.
//Being responsible only for one thing, it will have only one reason to change.


//On screen: Report #1 was registered., and later the final list.
//What proves it: three classes, three jobs. The storage saves but never prints, and the printer prints but never saves.
// SOLID principle 1: Single Responsibility Principle (SRP).


#pragma once

#include <string>
#include <vector>

// Job: hold the data of one problem reported by a citizen.
struct Report {
    int id;
    std::string category;     // for example "Pothole"
    std::string description;  // what the citizen wrote

    Report(std::string category, std::string description);
};

// Job: keep the reports. For now they stay in memory, in a vector.
class ReportStorage {
public:
    // Saves a report, gives it the next free id and returns that id.
    int add(Report report);

    // Returns every saved report.
    std::vector<Report> all();

private:
    std::vector<Report> reports;
    int nextId = 1;
};

// Job: show a report on the screen.
class ReportPrinter {
public:
    void print(const Report& report);
};
