#include "Lab2/crews/GarbageCrew.h"

#include <iostream>

#include "Lab2/workorders/WorkOrder.h"

using namespace std;

void GarbageCrew::work(const WorkOrder& order) const {
    cout << "the garbage crew cleans up at " << order.address << ".\n";
}
