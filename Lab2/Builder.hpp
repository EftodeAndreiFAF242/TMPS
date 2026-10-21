// Builder.hpp
//
// Creational pattern 2: Builder.
// "Build a complex object step by step, giving only the parts that are needed."
//
// When city hall accepts a report, it makes a work order for a repair crew.
// A work order has many parts, and most of them are optional:
// the priority, the deadline and the note have default values.
//
// Without a builder, a work order would come from a constructor with six parameters:
//   WorkOrder(1, "Pothole", "Stefan cel Mare Blvd. 12", "High", 2, "Put up a sign first")
// It is hard to read (which number is the id and which is the deadline?), easy to get
// wrong, and every mix of optional parts would need one more constructor.
// With the builder, every part has a name and the optional ones can be left out.

#pragma once

#include "../Lab1/SingleResponsibility.hpp"  // for Report

// The object that gets built: the job given to a repair crew.
struct WorkOrder {
    int reportId = 0;            // the report it comes from
    string problem;              // the category of the report, for example "Pothole"
    string address;              // where the crew has to go
    string priority = "Normal";  // optional
    int deadlineDays = 7;        // optional
    string note;                 // optional, empty if there is nothing to add
};

// Builds a WorkOrder one part at a time.
class WorkOrderBuilder {
public:
    // The parts every work order needs are asked for at the start,
    // so a work order without a report or without an address can't be built.
    WorkOrderBuilder(const Report& report, string address) {
        order.reportId = report.id;
        order.problem = report.category;
        order.address = address;
    }

    // The optional parts. Each method returns the same builder (*this),
    // so the calls can be written one after another: .setPriority(...).setDeadline(...)
    WorkOrderBuilder& setPriority(string priority) {
        order.priority = priority;
        return *this;
    }

    WorkOrderBuilder& setDeadline(int days) {
        order.deadlineDays = days;
        return *this;
    }

    WorkOrderBuilder& setNote(string note) {
        order.note = note;
        return *this;
    }

    // The last step: gives back the finished work order.
    WorkOrder build() {
        return order;
    }

private:
    WorkOrder order;  // the work order being built; it starts with the default values
};

// Shows a work order on the screen. It is a separate class, like ReportPrinter in lab 1.
class WorkOrderPrinter {
public:
    void print(const WorkOrder& order) {
        cout << "Work order for report #" << order.reportId << " (" << order.problem << ")\n";
        cout << "  address:  " << order.address << "\n";
        cout << "  priority: " << order.priority << "\n";
        cout << "  deadline: " << order.deadlineDays << " days\n";
        if (order.note != "") {
            cout << "  note:     " << order.note << "\n";
        }
    }
};
