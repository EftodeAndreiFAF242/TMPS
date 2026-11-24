// "Turn a request into an object so it can be queued, logged or undone"
// Lab 4 - Command: the Invoker, runs the operator's commands and keeps them for undo

#include "Lab4/operator/OperatorDesk.h"

#include <iostream>
#include <utility>

using namespace std;

string OperatorDesk::run(unique_ptr<Command> command) {
    cout << "Operator: " << command->name() << "\n";
    string refusal = command->execute();

    // Un pas refuzat nu se păstrează
    if (!refusal.empty()) {
        cout << "  refused: " << refusal << "\n";
        return refusal;
    }
    history.push_back(move(command));
    return "";
}

string OperatorDesk::undoLast() {
    if (history.empty()) {
        cout << "Operator: undo, but there is nothing to undo.\n";
        return "there is nothing to undo";
    }

    // The newest command goes first
    unique_ptr<Command> last = move(history.back());
    history.pop_back();
    cout << "Operator: undo \"" << last->name() << "\"\n";
    last->undo();
    return "";
}

size_t OperatorDesk::historySize() const {
    return history.size();
}
