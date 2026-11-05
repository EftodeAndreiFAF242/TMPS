// Lab 1 - Single Responsibility Principle (SRP): only keeps the reports

#include "Lab1/storage/ReportStorage.h"

using namespace std;

int ReportStorage::add(Report report) {
    report.id = nextId;
    nextId = nextId + 1;
    reports.push_back(report);
    return report.id;
}

vector<Report> ReportStorage::all() {
    return reports;
}
