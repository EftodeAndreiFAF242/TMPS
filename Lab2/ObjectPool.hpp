// ObjectPool.hpp
//
// Extra pattern (not required): Object Pool.
// "Keep a few ready objects and lend them out, instead of making a new one every time."
//
// City hall has a fixed number of service trucks. A crew borrows a truck for a job and gives
// it back when the job is done, and then the next crew gets that same truck.
// No truck is made for a single job, and a truck that is out can't be lent twice.
//
// Programs use the same idea for objects that are slow to make or that there are only a few of,
// for example connections to a database.

#pragma once

#include <vector>

using namespace std;

struct Truck {
    int number;
    bool inUse;

    Truck(int number) {
        this->number = number;
        this->inUse = false;
    }
};

class TruckPool {
public:
    // Every truck is made here, once, when the pool is made.
    TruckPool(int size) {
        for (int i = 1; i <= size; i++) {
            trucks.push_back(Truck(i));
        }
    }

    // Lends a free truck. Returns nullptr if every truck is in use.
    Truck* acquire() {
        for (Truck& truck : trucks) {
            if (!truck.inUse) {
                truck.inUse = true;
                return &truck;
            }
        }
        return nullptr;
    }

    // Takes a truck back, so it can be lent again.
    void release(Truck* truck) {
        if (truck != nullptr) {
            truck->inUse = false;
        }
    }

private:
    // The vector gets its trucks only in the constructor and never grows after that,
    // so the pointers that acquire() gives out always point to the right trucks.
    vector<Truck> trucks;
};
