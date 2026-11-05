#pragma once

#include <memory>

#include "Lab2/crews/Crew.h"
#include "Lab2/departments/Department.h"

// Takes care of the street lights. It sends a ElectricianCrew.
class LightingDepartment : public Department {
public:
    std::unique_ptr<Crew> createCrew() const override;
};
