// Lab 2 - Factory Method: a Concrete Product

#pragma once

#include "Lab2/crews/Crew.h"

// Repairs street lights.
class ElectricianCrew : public Crew {
public:
    void work(const WorkOrder& order) const override;
};
