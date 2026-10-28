//Creates an instance out of several related derived classes.
//It is usually used together with other creational design patterns

#pragma once

#include <memory>

struct WorkOrder;

class Crew {
public:
    virtual ~Crew() = default;
    virtual void work(const WorkOrder& order) const = 0;
};

class RoadCrew : public Crew {
public:
    void work(const WorkOrder& order) const override;
};

class ElectricianCrew : public Crew {
public:
    void work(const WorkOrder& order) const override;
};

class GarbageCrew : public Crew {
public:
    void work(const WorkOrder& order) const override;
};

class Department {
public:
    virtual ~Department() = default;

    virtual std::unique_ptr<Crew> createCrew() const = 0;

    void handle(const WorkOrder& order) const;
};

class RoadDepartment : public Department {
public:
    std::unique_ptr<Crew> createCrew() const override;
};

class LightingDepartment : public Department {
public:
    std::unique_ptr<Crew> createCrew() const override;
};

class SanitationDepartment : public Department {
public:
    std::unique_ptr<Crew> createCrew() const override;
};
