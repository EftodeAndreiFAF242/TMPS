// Text.hpp
// A small text helper shared by the validation rules and the service.

#pragma once

#include <algorithm>
#include <cctype>
#include <string_view>

using namespace std;

namespace civicdesk {

/// True when the text is empty or holds nothing but whitespace.
[[nodiscard]] inline bool isBlank(string_view text) {
    return ranges::all_of(text, [](unsigned char c) { return isspace(c) != 0; });
}

}  // namespace civicdesk
