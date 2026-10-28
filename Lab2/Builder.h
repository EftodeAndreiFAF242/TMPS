//Separates object construction from its representation so that the same construction process could create different representations.

#pragma once

#include <string>

struct Report;

struct WorkOrder {
    int reportId = 0;
    std::string problem;
    std::string address;
    std::string priority = "Normal";
    int deadlineDays = 7;
    std::string note;
};

class WorkOrderBuilder {
public:
    WorkOrderBuilder(const Report& report, const std::string& address);

    WorkOrderBuilder& setPriority(const std::string& priority);
    WorkOrderBuilder& setDeadline(int days);
    WorkOrderBuilder& setNote(const std::string& note);

    WorkOrder build() const;

private:
    WorkOrder order;
};

class WorkOrderPrinter {
public:
    void print(const WorkOrder& order) const;
};
