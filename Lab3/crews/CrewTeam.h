// Lab 3 - Composite: the Composite, a team of crews that works like one crew

#pragma once

#include <memory>
#include <vector>

#include "Lab2/crews/Crew.h"

// Some jobs need more than one crew. A team is a Crew made of other crews: when the team works,
// every crew in it works. Because a team is a Crew too, a department sends a team exactly the way
// it sends one crew, and a team can even have another team inside it.
class CrewTeam : public Crew {
public:
    // Adds a crew to the team. The team keeps it and deletes it when the team is deleted.
    void add(std::unique_ptr<Crew> member);

    void work(const WorkOrder& order) const override;

private:
    std::vector<std::unique_ptr<Crew>> members;
};
