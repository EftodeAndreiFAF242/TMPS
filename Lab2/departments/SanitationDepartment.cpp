// Lab 2 - Factory Method: a Concrete Creator, makes a GarbageCrew

#include "Lab2/departments/SanitationDepartment.h"

#include "Lab2/crews/GarbageCrew.h"

using namespace std;

unique_ptr<Crew> SanitationDepartment::createCrew() const {
    return make_unique<GarbageCrew>();
}
