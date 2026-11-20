// Lab 3 - Composite: a Concrete Creator (lab 2's Factory Method) that makes a CrewTeam instead of one crew

#pragma once

#include <memory>

#include "Lab2/crews/Crew.h"
#include "Lab2/departments/Department.h"

// Takes care of the damage after a storm. A storm leaves holes in the road and branches and trash
// everywhere, so this department sends a team: the road crew and the garbage crew together.
class StormDepartment : public Department {
public:
    std::unique_ptr<Crew> createCrew() const override;
};
