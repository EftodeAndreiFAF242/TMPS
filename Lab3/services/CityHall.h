// Lab 3 - Facade: the Facade, one simple entry point for everything city hall does with a report

#pragma once

#include <map>
#include <string>

#include "Lab1/reports/ReportService.h"
#include "Lab1/validation/DescriptionRule.h"
#include "Lab1/validation/Validator.h"
#include "Lab2/fleet/TruckPool.h"
#include "Lab2/workorders/WorkOrderPrinter.h"
#include "Lab3/map/CityMap.h"
#include "Lab3/messages/CrewComingMessage.h"
#include "Lab3/messages/WorkDoneMessage.h"
#include "Lab3/validation/KnownCategoryRule.h"

class Department;
class Notifier;
class ReportStorage;

// City hall as the citizen sees it: one call to report a problem. Behind that call it checks
// and saves the report, makes a work order, sends a crew with a truck and tells the citizen when
// the crew goes out and when the work is done, so the client does not have to know the classes
// of lab 1, lab 2 and lab 3 or the order they are used in.
class CityHall {
public:
    // City hall gets the storage and the way citizens are told, and makes the rest itself.
    CityHall(ReportStorage* storage, Notifier* notifier);

    // Tells city hall which department takes care of a category, and from then on the category is
    // known. A new department is a new class and one more call to this method, and the code of
    // CityHall stays the same.
    void addDepartment(const std::string& category, const Department* department);

    // Handles a problem from start to end. Returns false if the report was refused.
    bool reportProblem(const std::string& category, const std::string& description,
                       const std::string& address, bool urgent);

    // Shows the map with a marker for every report city hall accepted.
    void showMap() const;

private:
    ReportStorage* storage;
    std::map<std::string, const Department*> departments;  // the category and its department
    KnownCategoryRule categoryRule;                         // knows the categories from departments
    DescriptionRule descriptionRule;
    Validator validator;
    ReportService reportService;
    CrewComingMessage crewComingMessage;  // both messages travel through the notifier city hall got
    WorkDoneMessage workDoneMessage;
    TruckPool trucks;
    WorkOrderPrinter orderPrinter;
    CityMap cityMap;
};
