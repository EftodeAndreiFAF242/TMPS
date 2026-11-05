// Lab 2 - Factory Method: the Product (interface)

#pragma once

struct WorkOrder;

// A team that goes out and does the job written in a work order.
class Crew {
public:
    virtual ~Crew() = default;
    virtual void work(const WorkOrder& order) const = 0;
};
