#include "Lab2/crews/RoadCrew.h"

#include <iostream>

#include "Lab2/workorders/WorkOrder.h"

using namespace std;

void RoadCrew::work(const WorkOrder& order) const {
    cout << "the road crew fills the pothole at " << order.address << ".\n";
}
