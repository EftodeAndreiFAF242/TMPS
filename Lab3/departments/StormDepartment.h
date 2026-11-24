// "It lets clients treat simple and complex objects uniformly."
// Lab 3 - Composite: a Concrete Creator (lab 2's Factory Method) that makes a CrewTeam instead of one crew

#pragma once

#include <memory>

#include "Lab2/crews/Crew.h"
#include "Lab2/departments/Department.h"

// After a storm: road and garbage crews
class StormDepartment : public Department {
public:
    std::unique_ptr<Crew> createCrew() const override;
};
