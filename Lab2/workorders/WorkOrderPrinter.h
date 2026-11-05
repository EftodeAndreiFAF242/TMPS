// Lab 2 - Builder: shows the product that was built

#pragma once

struct WorkOrder;

// Shows a work order on the screen.
class WorkOrderPrinter {
public:
    void print(const WorkOrder& order) const;
};
