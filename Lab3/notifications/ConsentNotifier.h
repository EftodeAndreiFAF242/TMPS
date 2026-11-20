// Lab 3 - Proxy: the Proxy, stands in front of a notifier and lets a message through only with consent

#pragma once

#include <string>

#include "Lab1/notifications/Notifier.h"

// Some citizens don't want to get messages in a certain way, for example letters. City hall has to
// respect that, but ReportService and CityHall should not check it before every message. This proxy
// stands in front of the real notifier, with the same send(), and controls the access to it: if the
// citizen agreed, the message goes to the real notifier exactly as it came; if not, nothing is sent.
class ConsentNotifier : public Notifier {
public:
    ConsentNotifier(Notifier* realNotifier, bool citizenAgreed);

    void send(const std::string& message) override;

private:
    Notifier* realNotifier;  // the Real Subject: the notifier that really sends the message
    bool citizenAgreed;      // what the citizen answered when city hall asked for consent
};
