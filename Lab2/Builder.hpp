//Separates object construction from its representation so that the same construction process could create different representations.

#pragma once

#include "../Lab1/SingleResponsibility.hpp"

struct WorkOrder {
    int reportId = 0;
    string problem;
    string address;
    string priority = "Normal";
    int deadlineDays = 7;
    string note;
};

class WorkOrderBuilder {
public:
    WorkOrderBuilder(const Report& report, const string& address) {
        order.reportId = report.id;
        order.problem = report.category;
        order.address = address;
    }

    WorkOrderBuilder& setPriority(const string& priority) {
        order.priority = priority;
        return *this;
    }

    WorkOrderBuilder& setDeadline(int days) {
        order.deadlineDays = days;
        return *this;
    }

    WorkOrderBuilder& setNote(const string& note) {
        order.note = note;
        return *this;
    }

    WorkOrder build() const {
        return order;
    }

private:
    WorkOrder order;
};

class WorkOrderPrinter {
public:
    void print(const WorkOrder& order) const {
        cout << "Work order for report #" << order.reportId << " (" << order.problem << ")\n";
        cout << "  address:  " << order.address << "\n";
        cout << "  priority: " << order.priority << "\n";
        cout << "  deadline: " << order.deadlineDays << " days\n";
        if (!order.note.empty()) {
            cout << "  note:     " << order.note << "\n";
        }
    }
};
