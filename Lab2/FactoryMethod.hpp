//Creates an instance out of several related derived classes.
//It is usually used together with other creational design patterns

#pragma once

#include <memory>

#include "Builder.hpp"

class Crew {
public:
    virtual ~Crew() = default;
    virtual void work(const WorkOrder& order) const = 0;
};

class RoadCrew : public Crew {
public:
    void work(const WorkOrder& order) const override {
        cout << "the road crew fills the pothole at " << order.address << ".\n";
    }
};

class ElectricianCrew : public Crew {
public:
    void work(const WorkOrder& order) const override {
        cout << "the electricians repair the street light at " << order.address << ".\n";
    }
};

class GarbageCrew : public Crew {
public:
    void work(const WorkOrder& order) const override {
        cout << "the garbage crew cleans up at " << order.address << ".\n";
    }
};

class Department {
public:
    virtual ~Department() = default;

    virtual unique_ptr<Crew> createCrew() const = 0;

    void handle(const WorkOrder& order) const {
        cout << "Report #" << order.reportId << " (" << order.priority << " priority, "
             << order.deadlineDays << " days): ";

        unique_ptr<Crew> crew = createCrew();
        crew->work(order);
    }
};

class RoadDepartment : public Department {
public:
    unique_ptr<Crew> createCrew() const override {
        return make_unique<RoadCrew>();
    }
};

class LightingDepartment : public Department {
public:
    unique_ptr<Crew> createCrew() const override {
        return make_unique<ElectricianCrew>();
    }
};

class SanitationDepartment : public Department {
public:
    unique_ptr<Crew> createCrew() const override {
        return make_unique<GarbageCrew>();
    }
};
