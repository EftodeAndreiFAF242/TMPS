// Lab 1 - Dependency Inversion Principle (DIP): a low-level detail that implements Notifier

#pragma once

#include <string>

#include "Lab1/notifications/Notifier.h"

// Pretends to send an e-mail. A real one would talk to a mail server.
class EmailNotifier : public Notifier {
public:
    void send(const std::string& message) override;
};
