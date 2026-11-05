// Lab 3 - Decorator: the Decorator, the base class of every notifier that wraps another one

#pragma once

#include <string>

#include "Lab1/notifications/Notifier.h"

// A notifier that wraps another notifier and adds something to what it does. It is a Notifier
// itself, so a wrapped notifier can be used anywhere a plain one can, and it can be wrapped again.
class NotifierDecorator : public Notifier {
public:
    explicit NotifierDecorator(Notifier* wrapped);

    // Passes the message on to the wrapped notifier.
    void send(const std::string& message) override;

private:
    Notifier* wrapped;
};
