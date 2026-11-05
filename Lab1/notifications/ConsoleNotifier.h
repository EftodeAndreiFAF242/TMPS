// Lab 1 - Dependency Inversion Principle (DIP): a low-level detail that implements Notifier

#pragma once

#include <string>

#include "Lab1/notifications/Notifier.h"

// Writes the message on the screen.
class ConsoleNotifier : public Notifier {
public:
    void send(const std::string& message) override;
};
