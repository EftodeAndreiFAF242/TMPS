// "Provides a unified interface that represents multiple components."
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
#include "Lab3/calendar/Calendar.h"

using namespace std;

CityHall::CityHall(ReportStorage* storage, Notifier* notifier, const Calendar* calendar)
    : storage(storage),
      calendar(calendar),
      categoryRule(&departments),
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
    // Step 1: check, save, tell the citizen
    if (!reportService.submit(Report(category, description))) {
        return false;
    }
    vector<Report> reports = storage->all();
    const Report& report = reports.back();  // raportul abia salvat

    // Pasul 2: ordinul de lucru (Builder)
    WorkOrderBuilder builder(report, address);
    if (urgent) {
        builder.setPriority("High").setDeadline(2);
    }
    WorkOrder order = builder.build();
    orderPrinter.print(order);

    // The adapter gives the real date
    cout << "  done by:  " << calendar->dateIn(order.deadlineDays) << "\n";

    // Step 3: truck, crew, truck back
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
