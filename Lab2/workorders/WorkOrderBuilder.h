// Lab 2 - Builder: the builder, makes a WorkOrder step by step

#pragma once

#include <string>

#include "Lab2/workorders/WorkOrder.h"

struct Report;

// Makes a work order step by step. The required parts go in the constructor,
// each optional part has its own method, and build() returns the finished order.
class WorkOrderBuilder {
public:
    WorkOrderBuilder(const Report& report, const std::string& address);

    WorkOrderBuilder& setPriority(const std::string& priority);
    WorkOrderBuilder& setDeadline(int days);
    WorkOrderBuilder& setNote(const std::string& note);

    WorkOrder build() const;

private:
    WorkOrder order;
};
