#include "Lab1/reports/ReportPrinter.h"

#include <iostream>

#include "Lab1/reports/Report.h"

using namespace std;

void ReportPrinter::print(const Report& report) {
    cout << "#" << report.id << " [" << report.category << "] " << report.description << "\n";
}
