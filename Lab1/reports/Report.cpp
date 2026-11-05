// Lab 1 - Single Responsibility Principle (SRP): only holds the data of a report

#include "Lab1/reports/Report.h"

using namespace std;

Report::Report(string category, string description) {
    this->id = 0;  // the real id is given by the storage when the report is saved
    this->category = category;
    this->description = description;
}
