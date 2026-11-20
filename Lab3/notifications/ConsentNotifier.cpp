// Lab 3 - Proxy: the Proxy, stands in front of a notifier and lets a message through only with consent

#include "Lab3/notifications/ConsentNotifier.h"

#include <iostream>

using namespace std;

ConsentNotifier::ConsentNotifier(Notifier* realNotifier, bool citizenAgreed) {
    this->realNotifier = realNotifier;
    this->citizenAgreed = citizenAgreed;
}

void ConsentNotifier::send(const string& message) {
    // The access check comes first. Without consent, the real notifier is never called.
    if (!citizenAgreed) {
        cout << "[consent] The citizen did not agree to get messages this way, so this one is not sent.\n";
        return;
    }

    // With consent, the call goes on unchanged: the same message, to the same send().
    realNotifier->send(message);
}
