#pragma once

// One truck of city hall. A crew borrows it for a job and gives it back after.
struct Truck {
    int number;
    bool inUse = false;

    explicit Truck(int number);
};
