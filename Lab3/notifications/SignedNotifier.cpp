// Lab 3 - Decorator: a Concrete Decorator, adds the city hall signature to every message

#include "Lab3/notifications/SignedNotifier.h"

using namespace std;

SignedNotifier::SignedNotifier(Notifier* wrapped) : NotifierDecorator(wrapped) {}

void SignedNotifier::send(const string& message) {
    // The added part: the signature. Sending the message is still the wrapped notifier's job.
    NotifierDecorator::send(message + " -- Chisinau City Hall");
}
