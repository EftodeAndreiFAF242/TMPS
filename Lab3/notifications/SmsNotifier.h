// Lab 3 - Adapter: the Adapter, lets any code that uses Notifier send SMS through SmsGateway

#pragma once

#include <string>

#include "Lab1/notifications/Notifier.h"

class SmsGateway;

// Turns the Notifier interface into calls to SmsGateway, so ReportService and the other
// classes from lab 1 can send SMS without any change.
class SmsNotifier : public Notifier {
public:
    SmsNotifier(SmsGateway* gateway, const std::string& phoneNumber);

    void send(const std::string& message) override;

private:
    SmsGateway* gateway;      // the class that really sends the SMS
    std::string phoneNumber;  // SmsGateway needs it, but Notifier::send() does not have it
};
