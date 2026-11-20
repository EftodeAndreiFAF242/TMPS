// Lab 3 - Composite: the Composite, a team of crews that works like one crew

#pragma once

#include <memory>
#include <vector>

#include "Lab2/crews/Crew.h"

// O echipă din mai multe echipaje
class CrewTeam : public Crew {
public:
    // The team now owns the crew
    void add(std::unique_ptr<Crew> member);

    void work(const WorkOrder& order) const override;

private:
    std::vector<std::unique_ptr<Crew>> members;
};
