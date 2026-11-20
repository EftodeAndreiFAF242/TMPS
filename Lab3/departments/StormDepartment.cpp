// Lab 3 - Composite: a Concrete Creator (lab 2's Factory Method) that makes a CrewTeam instead of one crew

#include "Lab3/departments/StormDepartment.h"

#include "Lab2/crews/GarbageCrew.h"
#include "Lab2/crews/RoadCrew.h"
#include "Lab3/crews/CrewTeam.h"

using namespace std;

unique_ptr<Crew> StormDepartment::createCrew() const {
    unique_ptr<CrewTeam> team = make_unique<CrewTeam>();
    team->add(make_unique<RoadCrew>());
    team->add(make_unique<GarbageCrew>());

    // Echipa se trimite ca un echipaj
    return team;
}
