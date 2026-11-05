// Lab 3 - Decorator: a Concrete Decorator, keeps a copy of every message that was sent

#pragma once

#include <string>
#include <vector>

#include "Lab3/notifications/NotifierDecorator.h"

// Keeps a copy of every message, so city hall can see later what it told the citizens.
class ArchivedNotifier : public NotifierDecorator {
public:
    explicit ArchivedNotifier(Notifier* wrapped);

    void send(const std::string& message) override;

    // Every message sent through this notifier, in the order they were sent.
    const std::vector<std::string>& getHistory() const;

private:
    std::vector<std::string> history;
};
