// Lab 2 - Builder: the builder, makes a WorkOrder step by step

#include "Lab2/workorders/WorkOrderBuilder.h"

#include "Lab1/reports/Report.h"

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
