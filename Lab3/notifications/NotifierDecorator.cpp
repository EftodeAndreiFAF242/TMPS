// Lab 3 - Decorator: the Decorator, the base class of every notifier that wraps another one

#include "Lab3/notifications/NotifierDecorator.h"

using namespace std;

NotifierDecorator::NotifierDecorator(Notifier* wrapped) {
    this->wrapped = wrapped;
}

void NotifierDecorator::send(const string& message) {
    wrapped->send(message);
}
