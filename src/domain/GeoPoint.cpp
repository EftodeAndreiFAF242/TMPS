#include "domain/GeoPoint.hpp"

#include <algorithm>
#include <cmath>
#include <numbers>

namespace civicdesk {

double distanceMeters(const GeoPoint& a, const GeoPoint& b) noexcept {
    constexpr double kEarthRadiusMeters = 6'371'000.0;
    constexpr double kDegreesToRadians = std::numbers::pi / 180.0;

    const double latA = a.latitude * kDegreesToRadians;
    const double latB = b.latitude * kDegreesToRadians;
    const double halfLatDelta = (latB - latA) / 2.0;
    const double halfLngDelta = (b.longitude - a.longitude) * kDegreesToRadians / 2.0;

    const double h = std::sin(halfLatDelta) * std::sin(halfLatDelta) +
                     std::cos(latA) * std::cos(latB) * std::sin(halfLngDelta) * std::sin(halfLngDelta);

    // Rounding can push h a hair above 1 for antipodal points, where asin is undefined.
    return 2.0 * kEarthRadiusMeters * std::asin(std::min(1.0, std::sqrt(h)));
}

}  // namespace civicdesk
