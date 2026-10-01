#pragma once

#include <string>
#include <utility>
#include <vector>

namespace civicdesk {

/// Everything that is wrong with a draft. No errors means the draft is valid.
class ValidationResult {
public:
    void addError(std::string message) { errors_.push_back(std::move(message)); }

    [[nodiscard]] bool ok() const noexcept { return errors_.empty(); }
    [[nodiscard]] const std::vector<std::string>& errors() const noexcept { return errors_; }

private:
    std::vector<std::string> errors_;
};

}  // namespace civicdesk
