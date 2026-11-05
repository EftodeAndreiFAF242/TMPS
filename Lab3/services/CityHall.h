// Lab 3 - Facade: the Facade, one simple entry point for everything city hall does with a report

#pragma once

#include <string>

#include "Lab1/reports/ReportService.h"
#include "Lab1/validation/CategoryRule.h"
#include "Lab1/validation/DescriptionRule.h"
#include "Lab1/validation/Validator.h"
#include "Lab2/departments/Department.h"
#include "Lab2/departments/LightingDepartment.h"
#include "Lab2/departments/RoadDepartment.h"
#include "Lab2/departments/SanitationDepartment.h"
#include "Lab2/fleet/TruckPool.h"
#include "Lab2/workorders/WorkOrderPrinter.h"

class Notifier;
class ReportStorage;

// City hall as the citizen sees it: one call to report a problem. Behind that call it checks
// and saves the report, makes a work order and sends a crew with a truck, so the client does
// not have to know the classes of lab 1 and lab 2 or the order they are used in.
class CityHall {
public:
    // City hall gets the storage and the way citizens are told, and makes everything else itself.
    CityHall(ReportStorage* storage, Notifier* notifier);

    // Handles a problem from start to end. Returns false if the report was refused.
    bool reportProblem(const std::string& category, const std::string& description,
                       const std::string& address, bool urgent);

private:
    // The department that takes care of a category.
    const Department& departmentFor(const std::string& category) const;

    ReportStorage* storage;
    CategoryRule categoryRule;
    DescriptionRule descriptionRule;
    Validator validator;
    ReportService reportService;
    RoadDepartment roads;
    LightingDepartment lighting;
    SanitationDepartment sanitation;
    TruckPool trucks;
    WorkOrderPrinter orderPrinter;
};
