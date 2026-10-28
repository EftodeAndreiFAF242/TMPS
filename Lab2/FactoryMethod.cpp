#include "Lab2/FactoryMethod.h"

#include <iostream>

#include "Lab2/Builder.h"

using namespace std;

void RoadCrew::work(const WorkOrder& order) const {
    cout << "the road crew fills the pothole at " << order.address << ".\n";
}

void ElectricianCrew::work(const WorkOrder& order) const {
    cout << "the electricians repair the street light at " << order.address << ".\n";
}

void GarbageCrew::work(const WorkOrder& order) const {
    cout << "the garbage crew cleans up at " << order.address << ".\n";
}

void Department::handle(const WorkOrder& order) const {
    cout << "Report #" << order.reportId << " (" << order.priority << " priority, "
         << order.deadlineDays << " days): ";

    unique_ptr<Crew> crew = createCrew();
    crew->work(order);
}

unique_ptr<Crew> RoadDepartment::createCrew() const {
    return make_unique<RoadCrew>();
}

unique_ptr<Crew> LightingDepartment::createCrew() const {
    return make_unique<ElectricianCrew>();
}

unique_ptr<Crew> SanitationDepartment::createCrew() const {
    return make_unique<GarbageCrew>();
}
