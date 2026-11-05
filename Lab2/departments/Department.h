// Lab 2 - Factory Method: the Creator, declares the factory method createCrew()

#pragma once

#include <memory>

#include "Lab2/crews/Crew.h"

struct WorkOrder;

// A department of city hall. Every department handles a work order in the same steps,
// and only the kind of crew it sends is different.
class Department {
public:
    virtual ~Department() = default;

    // Makes the crew this department sends. Each department chooses its own.
    virtual std::unique_ptr<Crew> createCrew() const = 0;

    // Sends a crew to do the work order.
    void handle(const WorkOrder& order) const;
};
