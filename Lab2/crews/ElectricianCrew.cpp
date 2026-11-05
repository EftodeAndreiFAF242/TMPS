#include "Lab2/crews/ElectricianCrew.h"

#include <iostream>

#include "Lab2/workorders/WorkOrder.h"

using namespace std;

void ElectricianCrew::work(const WorkOrder& order) const {
    cout << "the electricians repair the street light at " << order.address << ".\n";
}
