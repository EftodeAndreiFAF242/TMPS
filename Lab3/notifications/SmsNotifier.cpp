// Lab 3 - Adapter: the Adapter, lets any code that uses Notifier send SMS through SmsGateway

#include "Lab3/notifications/SmsNotifier.h"

#include <iostream>

#include "Lab3/external/SmsGateway.h"

using namespace std;

SmsNotifier::SmsNotifier(SmsGateway* gateway, const string& phoneNumber) {
    this->gateway = gateway;
    this->phoneNumber = phoneNumber;
}

void SmsNotifier::send(const string& message) {
    // Notifier gives a std::string, and SmsGateway wants C-style text, so the adapter converts it.
    int status = gateway->sendSms(phoneNumber.c_str(), message.c_str());

    // SmsGateway answers with a code instead of telling anyone, so the adapter checks it.
    if (status != 0) {
        cout << "[sms] The message could not be sent (error " << status << ").\n";
    }
}
