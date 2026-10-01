#pragma once

#include <algorithm>
#include <cctype>
#include <string_view>

namespace civicdesk {

/// True when the text is empty or holds nothing but whitespace.
[[nodiscard]] inline bool isBlank(std::string_view text) {
    return std::ranges::all_of(text, [](unsigned char c) { return std::isspace(c) != 0; });
}

}  // namespace civicdesk
