// GeoPoint.cpp
// Implementation of the distance between two points on the map.

#include "domain/GeoPoint.hpp"

#include <algorithm>
#include <cmath>
#include <numbers>

using namespace std;

namespace civicdesk {

// Haversine formula: the length of the shortest path between two points on a sphere.
double distanceMeters(const GeoPoint& a, const GeoPoint& b) noexcept {
    constexpr double kEarthRadiusMeters = 6'371'000.0;
    constexpr double kDegreesToRadians = numbers::pi / 180.0;

    // The coordinates are in degrees, the trigonometric functions work in radians.
    const double latA = a.latitude * kDegreesToRadians;
    const double latB = b.latitude * kDegreesToRadians;
    const double halfLatDelta = (latB - latA) / 2.0;
    const double halfLngDelta = (b.longitude - a.longitude) * kDegreesToRadians / 2.0;

    const double h = sin(halfLatDelta) * sin(halfLatDelta) +
                     cos(latA) * cos(latB) * sin(halfLngDelta) * sin(halfLngDelta);

    // Rounding can push h a hair above 1 for antipodal points, where asin is undefined.
    return 2.0 * kEarthRadiusMeters * asin(min(1.0, sqrt(h)));
}

}  // namespace civicdesk
