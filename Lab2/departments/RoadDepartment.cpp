// Lab 2 - Factory Method: a Concrete Creator, makes a RoadCrew

#include "Lab2/departments/RoadDepartment.h"

#include "Lab2/crews/RoadCrew.h"

using namespace std;

unique_ptr<Crew> RoadDepartment::createCrew() const {
    return make_unique<RoadCrew>();
}
