// "Turn a request into an object so it can be queued, logged or undone"
// Lab 4 - Command: the Invoker, runs the operator's commands and keeps them for undo

#pragma once

#include <cstddef>
#include <memory>
#include <string>
#include <vector>

#include "Lab4/operator/Command.h"

// Biroul operatorului de la primărie
class OperatorDesk {
public:
    // Runs it, keeps it if done
    std::string run(std::unique_ptr<Command> command);

    // Takes back the newest command
    std::string undoLast();

    // Câte comenzi se pot anula
    std::size_t historySize() const;

private:
    std::vector<std::unique_ptr<Command>> history;
};
