#pragma once

#include <vector>

struct Truck {
    int number;
    bool inUse = false;

    explicit Truck(int number);
};

class TruckPool {
public:
    explicit TruckPool(int size);

    Truck* acquire();
    void release(Truck* truck);

private:
    std::vector<Truck> trucks;
};
