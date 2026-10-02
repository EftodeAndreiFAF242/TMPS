// IIdGenerator.hpp
// Port: where the ids of new reports come from. ReportService depends on this interface, not on a counter (DIP).

#pragma once

#include "domain/Types.hpp"

namespace civicdesk {

/// Hands out identifiers for new reports. Every call returns an id never returned before.
///
/// DIP: the service needs a fresh id and doesn't care whether it is a counter or a UUID.
class IIdGenerator {
public:
    virtual ~IIdGenerator() = default;

    [[nodiscard]] virtual ReportId next() = 0;
};

}  // namespace civicdesk
