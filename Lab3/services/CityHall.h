// Lab 3 - Facade: the Facade, one simple entry point for everything city hall does with a report

#pragma once

#include <map>
#include <string>

#include "Lab1/reports/ReportService.h"
#include "Lab1/validation/DescriptionRule.h"
#include "Lab1/validation/Validator.h"
#include "Lab2/fleet/TruckPool.h"
#include "Lab2/workorders/WorkOrderPrinter.h"
#include "Lab3/validation/KnownCategoryRule.h"

class Calendar;
class Department;
class Notifier;
class ReportStorage;

// Un singur apel pentru tot sistemul
class CityHall {
public:
    // Gets storage, notifier and calendar
    CityHall(ReportStorage* storage, Notifier* notifier, const Calendar* calendar);

    // The department brings its category
    void addDepartment(const std::string& category, const Department* department);

    // Tratează problema de la început la sfârșit
    bool reportProblem(const std::string& category, const std::string& description,
                       const std::string& address, bool urgent);

private:
    ReportStorage* storage;
    const Calendar* calendar;                               // any calendar, here the adapter
    std::map<std::string, const Department*> departments;  // categoria și departamentul ei
    KnownCategoryRule categoryRule;                         // categories come from the departments
    DescriptionRule descriptionRule;
    Validator validator;
    ReportService reportService;
    TruckPool trucks;
    WorkOrderPrinter orderPrinter;
};
