#include "Lab1/SingleResponsibility.h"

#include <iostream>

using namespace std;

Report::Report(string category, string description) {
    this->id = 0;  // the real id is given by the storage when the report is saved
    this->category = category;
    this->description = description;
}

int ReportStorage::add(Report report) {
    report.id = nextId;
    nextId = nextId + 1;
    reports.push_back(report);
    return report.id;
}

vector<Report> ReportStorage::all() {
    return reports;
}

void ReportPrinter::print(const Report& report) {
    cout << "#" << report.id << " [" << report.category << "] " << report.description << "\n";
}
