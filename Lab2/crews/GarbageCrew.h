#pragma once

#include "Lab2/crews/Crew.h"

// Cleans up garbage.
class GarbageCrew : public Crew {
public:
    void work(const WorkOrder& order) const override;
};
