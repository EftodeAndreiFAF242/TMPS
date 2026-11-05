// Lab 2 - Builder: the builder, makes a WorkOrder step by step

#include "Lab2/workorders/WorkOrderBuilder.h"

#include "Lab1/reports/Report.h"
#include "Lab2/config/AppConfig.h"

using namespace std;

WorkOrderBuilder::WorkOrderBuilder(const Report& report, const string& address) {
    order.reportId = report.id;
    order.problem = report.category;
    order.address = address;

    // The optional parts start with the default values from the settings.
    const AppConfig& config = AppConfig::getInstance();
    order.priority = config.getDefaultPriority();
    order.deadlineDays = config.getDefaultDeadlineDays();
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
