// Lab 3 - Decorator: a Concrete Decorator, keeps a copy of every message that was sent

#include "Lab3/notifications/ArchivedNotifier.h"

using namespace std;

ArchivedNotifier::ArchivedNotifier(Notifier* wrapped) : NotifierDecorator(wrapped) {}

void ArchivedNotifier::send(const string& message) {
    // The added part: the copy. Sending the message is still the wrapped notifier's job.
    history.push_back(message);
    NotifierDecorator::send(message);
}

const vector<string>& ArchivedNotifier::getHistory() const {
    return history;
}
