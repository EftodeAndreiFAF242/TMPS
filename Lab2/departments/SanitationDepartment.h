#pragma once

#include <memory>

#include "Lab2/crews/Crew.h"
#include "Lab2/departments/Department.h"

// Keeps the city clean. It sends a GarbageCrew.
class SanitationDepartment : public Department {
public:
    std::unique_ptr<Crew> createCrew() const override;
};
