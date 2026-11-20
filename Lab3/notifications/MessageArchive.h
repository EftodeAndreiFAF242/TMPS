// Lab 3 - Decorator: the archive that ArchivedNotifier writes into (a plain class, not a role of the pattern)

#pragma once

#include <string>
#include <vector>

// The archive of city hall: a copy of every message it sent to the citizens.
class MessageArchive {
public:
    void add(const std::string& message);

    // Every message in the archive, in the order they were added.
    const std::vector<std::string>& all() const;

private:
    std::vector<std::string> messages;
};
