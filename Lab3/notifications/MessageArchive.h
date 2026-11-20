// Lab 3 - Decorator: the archive that ArchivedNotifier writes into (a plain class, not a role of the pattern)

#pragma once

#include <string>
#include <vector>

// The archive of sent messages
class MessageArchive {
public:
    void add(const std::string& message);

    // Toate mesajele, în ordinea lor
    const std::vector<std::string>& all() const;

private:
    std::vector<std::string> messages;
};
