// Lab 3 - Decorator: a Concrete Decorator, keeps a copy of every message that was sent

#pragma once

#include <string>

#include "Lab3/notifications/NotifierDecorator.h"

class MessageArchive;

// Keeps a copy of every message in the archive of city hall, so city hall can see later what it
// told the citizens. The archive is given from outside, so this class has only send(), like every
// other notifier, and whoever reads the archive does not need to know which notifier wrote it.
class ArchivedNotifier : public NotifierDecorator {
public:
    ArchivedNotifier(Notifier* wrapped, MessageArchive* archive);

    void send(const std::string& message) override;

private:
    MessageArchive* archive;
};
