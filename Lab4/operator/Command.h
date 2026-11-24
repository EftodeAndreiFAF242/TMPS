// "Turn a request into an object so it can be queued, logged or undone"
// Lab 4 - Command: the Command, one step the operator does on a case

#pragma once

#include <string>

// Un pas care se poate anula
class Command {
public:
    virtual ~Command() {}

    // What the operator does, in words
    virtual std::string name() const = 0;

    // Empty text = done, else why not
    virtual std::string execute() = 0;
    virtual void undo() = 0;
};
