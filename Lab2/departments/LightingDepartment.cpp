#include "Lab2/departments/LightingDepartment.h"

#include "Lab2/crews/ElectricianCrew.h"

using namespace std;

unique_ptr<Crew> LightingDepartment::createCrew() const {
    return make_unique<ElectricianCrew>();
}
