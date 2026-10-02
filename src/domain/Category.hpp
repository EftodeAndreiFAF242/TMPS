// Category.hpp
// The kinds of problems a citizen can report, and their names as text.

#pragma once

#include <string_view>

using namespace std;

namespace civicdesk {

/// The kind of urban problem a citizen can report.
enum class Category {
    Pothole,
    StreetLight,
    Garbage,
    RoadDamage,
    GreenSpace,
    Other,
};

/// Human-readable name of a category.
[[nodiscard]] constexpr string_view nameOf(Category category) noexcept {
    switch (category) {
        case Category::Pothole:     return "Pothole";
        case Category::StreetLight: return "Street light";
        case Category::Garbage:     return "Garbage";
        case Category::RoadDamage:  return "Road damage";
        case Category::GreenSpace:  return "Green space";
        case Category::Other:       return "Other";
    }
    return "Unknown";
}

}  // namespace civicdesk
