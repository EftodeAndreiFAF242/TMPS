#include "Lab2/Builder.h"

#include <iostream>

#include "Lab1/SingleResponsibility.h"

using namespace std;

WorkOrderBuilder::WorkOrderBuilder(const Report& report, const string& address) {
    order.reportId = report.id;
    order.problem = report.category;
    order.address = address;
}

WorkOrderBuilder& WorkOrderBuilder::setPriority(const string& priority) {
    order.priority = priority;
    return *this;
}

WorkOrderBuilder& WorkOrderBuilder::setDeadline(int days) {
    order.deadlineDays = days;
    return *this;
}

WorkOrderBuilder& WorkOrderBuilder::setNote(const string& note) {
    order.note = note;
    return *this;
}

WorkOrder WorkOrderBuilder::build() const {
    return order;
}

void WorkOrderPrinter::print(const WorkOrder& order) const {
    cout << "Work order for report #" << order.reportId << " (" << order.problem << ")\n";
    cout << "  address:  " << order.address << "\n";
    cout << "  priority: " << order.priority << "\n";
    cout << "  deadline: " << order.deadlineDays << " days\n";
    if (!order.note.empty()) {
        cout << "  note:     " << order.note << "\n";
    }
}
