// Lab 2 - Factory Method: a Concrete Product (no department makes it yet)

#pragma once

#include "Lab2/crews/Crew.h"

// Looks after parks and green spaces.
class GreenSpacesCrew : public Crew {
public:
    void work(const WorkOrder& order) const override;
};
