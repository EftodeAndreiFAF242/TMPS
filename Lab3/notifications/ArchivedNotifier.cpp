// "Add responsibilities to objects dynamically."
// Lab 3 - Decorator: a Concrete Decorator, keeps a copy of every message that was sent

#include "Lab3/notifications/ArchivedNotifier.h"

#include "Lab3/notifications/MessageArchive.h"

using namespace std;

ArchivedNotifier::ArchivedNotifier(Notifier* wrapped, MessageArchive* archive) : NotifierDecorator(wrapped) {
    this->archive = archive;
}

void ArchivedNotifier::send(const string& message) {
    // Întâi copia, apoi trimitem mesajul
    archive->add(message);
    NotifierDecorator::send(message);
}
