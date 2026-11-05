#pragma once

struct WorkOrder;

// Shows a work order on the screen.
class WorkOrderPrinter {
public:
    void print(const WorkOrder& order) const;
};
