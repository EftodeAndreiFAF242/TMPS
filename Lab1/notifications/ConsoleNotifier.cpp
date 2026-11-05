// Lab 1 - Dependency Inversion Principle (DIP): a low-level detail that implements Notifier

#include "Lab1/notifications/ConsoleNotifier.h"

#include <iostream>

using namespace std;

void ConsoleNotifier::send(const string& message) {
    cout << "[console] " << message << "\n";
}
