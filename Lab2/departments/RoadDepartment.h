// Lab 2 - Factory Method: a Concrete Creator, makes a RoadCrew

#pragma once

#include <memory>

#include "Lab2/crews/Crew.h"
#include "Lab2/departments/Department.h"

// Takes care of the roads. It sends a RoadCrew.
class RoadDepartment : public Department {
public:
    std::unique_ptr<Crew> createCrew() const override;
};
