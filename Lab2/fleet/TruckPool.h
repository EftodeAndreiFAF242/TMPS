// Lab 2 - Object Pool (extra): the pool that lends the trucks and takes them back

#pragma once

#include <vector>

#include "Lab2/fleet/Truck.h"

// Makes every truck once and lends them to the crews.
class TruckPool {
public:
    explicit TruckPool(int size);

    // Lends a free truck, or returns nullptr if every truck is in use.
    Truck* acquire();

    // Takes a truck back, so the next crew can use it.
    void release(Truck* truck);

private:
    std::vector<Truck> trucks;
};
