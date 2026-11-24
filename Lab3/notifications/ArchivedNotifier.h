// "Add responsibilities to objects dynamically."
// Lab 3 - Decorator: a Concrete Decorator, keeps a copy of every message that was sent

#pragma once

#include <string>

#include "Lab3/notifications/NotifierDecorator.h"

class MessageArchive;

// Keeps a copy of every message
class ArchivedNotifier : public NotifierDecorator {
public:
    ArchivedNotifier(Notifier* wrapped, MessageArchive* archive);

    void send(const std::string& message) override;

private:
    MessageArchive* archive;
};
