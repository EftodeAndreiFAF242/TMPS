// Lab 3 - Facade: the Facade, one simple entry point for everything city hall does with a report

#include "Lab3/services/CityHall.h"

#include <iostream>
#include <vector>

#include "Lab1/reports/Report.h"
#include "Lab1/storage/ReportStorage.h"
#include "Lab2/config/AppConfig.h"
#include "Lab2/departments/Department.h"
#include "Lab2/fleet/Truck.h"
#include "Lab2/workorders/WorkOrder.h"
#include "Lab2/workorders/WorkOrderBuilder.h"

using namespace std;

CityHall::CityHall(ReportStorage* storage, Notifier* notifier)
    : storage(storage),
      reportService(storage, &validator, notifier),
      trucks(AppConfig::getInstance().getTruckCount()) {
    validator.addRule(&categoryRule);
    validator.addRule(&descriptionRule);
}

void CityHall::addDepartment(const string& category, const Department* department) {
    departments[category] = department;
}

bool CityHall::reportProblem(const string& category, const string& description,
                             const string& address, bool urgent) {
    // Step 1 (lab 1): check the report, save it and tell the citizen.
    if (!reportService.submit(Report(category, description))) {
        return false;
    }
    vector<Report> reports = storage->all();
    const Report& report = reports.back();  // the report that was just saved

    // Step 2 (lab 2, Builder): make the work order. An urgent problem gets a high priority and
    // 2 days, the others keep the default values from the settings.
    WorkOrderBuilder builder(report, address);
    if (urgent) {
        builder.setPriority("High").setDeadline(2);
    }
    WorkOrder order = builder.build();
    orderPrinter.print(order);

    // Step 3 (lab 2, Object Pool and Factory Method): find the department of the category, borrow
    // a truck, let the department send its crew, and give the truck back when the job is done.
    if (departments.count(category) == 0) {
        cout << "No department takes care of \"" << category << "\" yet, so the work order waits.\n";
        return true;
    }
    Truck* truck = trucks.acquire();
    if (truck == nullptr) {
        cout << "No truck is free, so the work order waits.\n";
        return true;
    }
    cout << "Truck #" << truck->number << " goes out. ";
    departments[category]->handle(order);
    trucks.release(truck);
    return true;
}
