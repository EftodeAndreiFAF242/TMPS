#pragma once

namespace civicdesk {

/// A position on the map, in decimal degrees (WGS 84).
struct GeoPoint {
    double latitude{};
    double longitude{};

    friend bool operator==(const GeoPoint&, const GeoPoint&) = default;
};

/// Great-circle distance between two points, in metres (haversine formula).
[[nodiscard]] double distanceMeters(const GeoPoint& a, const GeoPoint& b) noexcept;

/// A rectangle on the map inside which city halls can act on a report.
struct ServiceArea {
    double south{};
    double north{};
    double west{};
    double east{};

    [[nodiscard]] constexpr bool contains(const GeoPoint& point) const noexcept {
        return point.latitude >= south && point.latitude <= north &&
               point.longitude >= west && point.longitude <= east;
    }
};

/// A rectangle around the Republic of Moldova, with a small margin.
inline constexpr ServiceArea kMoldova{.south = 45.4, .north = 48.6, .west = 26.5, .east = 30.2};

}  // namespace civicdesk
