// Lab 3 - Adapter: the Adaptee, a class whose interface does not match Notifier

#include "Lab3/external/SmsGateway.h"

#include <cstring>
#include <iostream>

using namespace std;

int SmsGateway::sendSms(const char* phoneNumber, const char* text) {
    if (phoneNumber == nullptr || strlen(phoneNumber) == 0) {
        return 1;  // error 1: there is no phone number
    }

    // A real gateway would send the message through the phone network.
    cout << "[sms to " << phoneNumber << "] " << text << "\n";
    return 0;
}
