#pragma once

#include <vector>

using namespace std;

struct Truck {
    int number;
    bool inUse = false;

    explicit Truck(int number) : number(number) {}
};

class TruckPool {
public:
    explicit TruckPool(int size) {
        trucks.reserve(size);
        for (int i = 1; i <= size; i++) {
            trucks.emplace_back(i);
        }
    }

    Truck* acquire() {
        for (Truck& truck : trucks) {
            if (!truck.inUse) {
                truck.inUse = true;
                return &truck;
            }
        }
        return nullptr;
    }

    void release(Truck* truck) {
        if (truck != nullptr) {
            truck->inUse = false;
        }
    }

private:
    vector<Truck> trucks;
};
