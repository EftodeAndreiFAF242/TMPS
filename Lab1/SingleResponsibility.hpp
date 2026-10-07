// SingleResponsibility.hpp
//
// SOLID principle 1: Single Responsibility Principle (SRP).
// "A class should have only one job, so it has only one reason to change."
//
// This file has three small classes, and each of them has one job:
//   Report        - holds the data of one report
//   ReportStorage - keeps the reports
//   ReportPrinter - shows a report on the screen
//
// The wrong way would be one big Report class that also saves itself and prints itself.
// Then every change to the storage or to the text on the screen would mean editing Report.

#pragma once

#include <iostream>
#include <string>
#include <vector>

using namespace std;

// Job: hold the data of one problem reported by a citizen.
struct Report {
    int id;
    string category;     // for example "Pothole"
    string description;  // what the citizen wrote

    Report(string category, string description) {
        this->id = 0;  // the real id is given by the storage when the report is saved
        this->category = category;
        this->description = description;
    }
};

// Job: keep the reports. For now they stay in memory, in a vector.
class ReportStorage {
public:
    // Saves a report, gives it the next free id and returns that id.
    int add(Report report) {
        report.id = nextId;
        nextId = nextId + 1;
        reports.push_back(report);
        return report.id;
    }

    // Returns every saved report.
    vector<Report> all() {
        return reports;
    }

private:
    vector<Report> reports;
    int nextId = 1;
};

// Job: show a report on the screen.
class ReportPrinter {
public:
    void print(const Report& report) {
        cout << "#" << report.id << " [" << report.category << "] " << report.description << "\n";
    }
};
