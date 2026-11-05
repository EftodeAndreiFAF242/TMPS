// Lab 1 - Dependency Inversion Principle (DIP): the abstraction

#pragma once

#include <string>

// Anything that can deliver a message to the citizen.
class Notifier {
public:
    virtual ~Notifier() {}
    virtual void send(const std::string& message) = 0;
};
