// Lab 3 - Adapter: the Adaptee, a class whose interface does not match Notifier

#pragma once

// The SMS service city hall bought from a phone company. The class comes from the company's
// library, so the project can't change it. Its interface does not match Notifier: it takes
// C-style text, it needs a phone number, and it answers with a status code.
class SmsGateway {
public:
    // Sends a text message. Returns 0 if it was sent, or an error code if it was not.
    int sendSms(const char* phoneNumber, const char* text);
};
