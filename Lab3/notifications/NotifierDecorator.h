// Lab 3 - Decorator: the Decorator, the base class of every notifier that wraps another one

#pragma once

#include <string>

#include "Lab1/notifications/Notifier.h"

// Wraps a notifier and adds something
class NotifierDecorator : public Notifier {
public:
    explicit NotifierDecorator(Notifier* wrapped);

    // Passes the message on
    void send(const std::string& message) override;

private:
    Notifier* wrapped;
};
