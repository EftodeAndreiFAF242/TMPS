// Lab 3 - Decorator: a Concrete Decorator, adds the city hall signature to every message

#pragma once

#include <string>

#include "Lab3/notifications/NotifierDecorator.h"

// Signs every message, so the citizen knows it really comes from city hall.
class SignedNotifier : public NotifierDecorator {
public:
    explicit SignedNotifier(Notifier* wrapped);

    void send(const std::string& message) override;
};
