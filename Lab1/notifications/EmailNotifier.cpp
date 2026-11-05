#include "Lab1/notifications/EmailNotifier.h"

#include <iostream>

using namespace std;

void EmailNotifier::send(const string& message) {
    cout << "[e-mail] " << message << "\n";
}
