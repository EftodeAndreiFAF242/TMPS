// Lab 2 - Builder: shows the product that was built

#include "Lab2/workorders/WorkOrderPrinter.h"

#include <iostream>

#include "Lab2/workorders/WorkOrder.h"

using namespace std;

void WorkOrderPrinter::print(const WorkOrder& order) const {
    cout << "Work order for report #" << order.reportId << " (" << order.problem << ")\n";
    cout << "  address:  " << order.address << "\n";
    cout << "  priority: " << order.priority << "\n";
    cout << "  deadline: " << order.deadlineDays << " days\n";
    if (!order.note.empty()) {
        cout << "  note:     " << order.note << "\n";
    }
}
