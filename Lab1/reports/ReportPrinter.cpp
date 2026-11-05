// Lab 1 - Single Responsibility Principle (SRP): only shows a report on the screen

#include "Lab1/reports/ReportPrinter.h"

#include <iostream>

#include "Lab1/reports/Report.h"

using namespace std;

void ReportPrinter::print(const Report& report) {
    cout << "#" << report.id << " [" << report.category << "] " << report.description << "\n";
}
