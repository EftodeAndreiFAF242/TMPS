// FactoryMethod.hpp
//
// Creational pattern 3: Factory Method.
// "The base class says when an object is made. Each subclass decides which class it is."
//
// Every department of city hall handles a work order the same way: it forms a crew,
// and the crew does the job. Only the kind of crew is different:
//   RoadDepartment       -> RoadCrew
//   LightingDepartment   -> ElectricianCrew
//   SanitationDepartment -> GarbageCrew
//
// So Department writes the common steps once, in handle(), and leaves one method without
// a body: createCrew(), the factory method. Each department writes it and makes its own crew.
// The name RoadCrew, or any other concrete crew, never appears in Department.
//
// The wrong way would be an "if" in handle() for every kind of crew. Then each new department
// would mean editing handle(). Here a new department is one new class (Open/Closed, lab 1).

#pragma once

#include "Builder.hpp"  // for WorkOrder

// The product: what every crew can do.
class Crew {
public:
    virtual ~Crew() {}
    virtual void work(const WorkOrder& order) = 0;
};

class RoadCrew : public Crew {
public:
    void work(const WorkOrder& order) override {
        cout << "the road crew fills the pothole at " << order.address << ".\n";
    }
};

class ElectricianCrew : public Crew {
public:
    void work(const WorkOrder& order) override {
        cout << "the electricians repair the street light at " << order.address << ".\n";
    }
};

class GarbageCrew : public Crew {
public:
    void work(const WorkOrder& order) override {
        cout << "the garbage crew cleans up at " << order.address << ".\n";
    }
};

// The creator: the steps every department follows.
class Department {
public:
    virtual ~Department() {}

    // The factory method. "= 0" means every department has to write its own.
    virtual Crew* createCrew() = 0;

    // The same code for every department. It works with any crew, because it only knows Crew.
    void handle(const WorkOrder& order) {
        cout << "Report #" << order.reportId << " (" << order.priority << " priority, "
             << order.deadlineDays << " days): ";

        Crew* crew = createCrew();  // the department that runs this code decides which crew is made
        crew->work(order);
        delete crew;                // the crew was made with "new", so it is deleted after the job
    }
};

class RoadDepartment : public Department {
public:
    Crew* createCrew() override {
        return new RoadCrew();
    }
};

class LightingDepartment : public Department {
public:
    Crew* createCrew() override {
        return new ElectricianCrew();
    }
};

class SanitationDepartment : public Department {
public:
    Crew* createCrew() override {
        return new GarbageCrew();
    }
};
