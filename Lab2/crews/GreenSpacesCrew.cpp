#include "Lab2/crews/GreenSpacesCrew.h"

#include <iostream>

#include "Lab2/workorders/WorkOrder.h"

using namespace std;

void GreenSpacesCrew::work(const WorkOrder& order) const {
    cout << "the green spaces crew waters the plants at " << order.address << ".\n";
}
