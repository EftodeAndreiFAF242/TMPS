// Lab 3 - Bridge: the Abstraction, what city hall tells the citizen, joined to a Notifier (how it travels)

#include "Lab3/messages/CitizenMessage.h"

#include "Lab1/notifications/Notifier.h"

using namespace std;

CitizenMessage::CitizenMessage(Notifier* channel) {
    this->channel = channel;
}

void CitizenMessage::sendAbout(const WorkOrder& order) {
    // The message decides what to say, and the channel decides how it travels.
    channel->send(text(order));
}
