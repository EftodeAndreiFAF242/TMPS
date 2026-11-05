#pragma once

#include "Lab2/crews/Crew.h"

// Fills potholes.
class RoadCrew : public Crew {
public:
    void work(const WorkOrder& order) const override;
};
