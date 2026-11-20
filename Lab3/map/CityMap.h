// Lab 3 - Flyweight: the Client, keeps the markers of the city map and gets their styles from the factory

#pragma once

#include <string>
#include <vector>

#include "Lab3/map/Marker.h"
#include "Lab3/map/MarkerStyleFactory.h"

// The city map, with a marker for every report. City hall gets thousands of reports a year, and a
// marker that kept its own icon would need 4096 bytes. Here a marker keeps only its report number,
// its address and a pointer to the shared style of its category.
class CityMap {
public:
    void addMarker(int reportId, const std::string& category, const std::string& address);

    // Draws every marker on the screen.
    void show() const;

    int markerCount() const;
    int styleCount() const;

private:
    std::vector<Marker> markers;
    MarkerStyleFactory styles;
};
