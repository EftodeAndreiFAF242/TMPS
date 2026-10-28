#include "Lab2/ObjectPool.h"

Truck::Truck(int number) : number(number) {}

TruckPool::TruckPool(int size) {
    trucks.reserve(size);
    for (int i = 1; i <= size; i++) {
        trucks.emplace_back(i);
    }
}

Truck* TruckPool::acquire() {
    for (Truck& truck : trucks) {
        if (!truck.inUse) {
            truck.inUse = true;
            return &truck;
        }
    }
    return nullptr;
}

void TruckPool::release(Truck* truck) {
    if (truck != nullptr) {
        truck->inUse = false;
    }
}
