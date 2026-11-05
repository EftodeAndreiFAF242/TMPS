#include "Lab2/departments/Department.h"

#include <iostream>

#include "Lab2/workorders/WorkOrder.h"

using namespace std;

void Department::handle(const WorkOrder& order) const {
    cout << "Report #" << order.reportId << " (" << order.priority << " priority, "
         << order.deadlineDays << " days): ";

    unique_ptr<Crew> crew = createCrew();
    crew->work(order);
}
