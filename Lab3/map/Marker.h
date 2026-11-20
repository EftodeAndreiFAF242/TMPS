// Lab 3 - Flyweight: one marker on the city map, its extrinsic state and a pointer to the shared style

#pragma once

#include <string>

class MarkerStyle;

// One marker on the city map. It keeps only what is different for each report, its number and its
// address, and points to the style of its category, which it shares with the other markers.
struct Marker {
    int reportId = 0;
    std::string address;
    const MarkerStyle* style = nullptr;
};
