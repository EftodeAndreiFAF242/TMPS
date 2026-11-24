// "Add responsibilities to objects dynamically."
// Lab 3 - Decorator: the archive that ArchivedNotifier writes into (a plain class, not a role of the pattern)

#include "Lab3/notifications/MessageArchive.h"

using namespace std;

void MessageArchive::add(const string& message) {
    messages.push_back(message);
}

const vector<string>& MessageArchive::all() const {
    return messages;
}
