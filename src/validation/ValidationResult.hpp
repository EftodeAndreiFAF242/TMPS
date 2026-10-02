// ValidationResult.hpp
// The list of problems found in a report draft.

#pragma once

#include <string>
#include <utility>
#include <vector>

using namespace std;

namespace civicdesk {

/// Everything that is wrong with a draft. No errors means the draft is valid.
class ValidationResult {
public:
    void addError(string message) { errors_.push_back(move(message)); }

    [[nodiscard]] bool ok() const noexcept { return errors_.empty(); }
    [[nodiscard]] const vector<string>& errors() const noexcept { return errors_; }

private:
    vector<string> errors_;
};

}  // namespace civicdesk
