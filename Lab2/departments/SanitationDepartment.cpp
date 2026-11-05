#include "Lab2/departments/SanitationDepartment.h"

#include "Lab2/crews/GarbageCrew.h"

using namespace std;

unique_ptr<Crew> SanitationDepartment::createCrew() const {
    return make_unique<GarbageCrew>();
}
