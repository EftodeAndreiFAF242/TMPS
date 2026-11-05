#pragma once

#include <string>

#include "Lab1/notifications/Notifier.h"

// Writes the message on the screen.
class ConsoleNotifier : public Notifier {
public:
    void send(const std::string& message) override;
};
