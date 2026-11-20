// Lab 3 - Flyweight: the Client, keeps the markers of the city map and gets their styles from the factory

#include "Lab3/map/CityMap.h"

#include <iostream>

#include "Lab3/map/MarkerStyle.h"

using namespace std;

void CityMap::addMarker(int reportId, const string& category, const string& address) {
    Marker marker;
    marker.reportId = reportId;
    marker.address = address;
    marker.style = styles.get(category);  // the same style for every marker of the category
    markers.push_back(marker);
}

void CityMap::show() const {
    cout << "The city map, " << markers.size() << " marker(s):\n";
    for (const Marker& marker : markers) {
        // The style is shared, so the marker gives it the part that is only its own.
        marker.style->draw(marker.reportId, marker.address);
    }
}

int CityMap::markerCount() const {
    return markers.size();
}

int CityMap::styleCount() const {
    return styles.count();
}
