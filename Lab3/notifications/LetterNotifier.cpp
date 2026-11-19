// Lab 3 - Adapter: the Adapter, lets any code that uses Notifier write paper letters with the C library

#include "Lab3/notifications/LetterNotifier.h"

#include <cstdio>
#include <iostream>

using namespace std;

LetterNotifier::LetterNotifier(const string& fileName, const string& homeAddress) {
    this->fileName = fileName;
    this->homeAddress = homeAddress;
}

void LetterNotifier::send(const string& message) {
    // Notifier has one call, and the C library needs three: open the file, write, close it.
    // "a" opens the file for adding at the end, so the letters written before are kept.
    FILE* file = fopen(fileName.c_str(), "a");

    // The C library does not tell anyone when it fails, it returns nullptr, so the adapter checks it.
    if (file == nullptr) {
        cout << "[letter] The letter could not be written: " << fileName << " can't be opened.\n";
        return;
    }

    // Notifier gives a std::string, and fputs wants C-style text, so the adapter converts it.
    string letter = "To: " + homeAddress + "\n" + message + "\n\n";
    if (fputs(letter.c_str(), file) == EOF) {
        cout << "[letter] The letter could not be written to " << fileName << ".\n";
    } else {
        cout << "[letter to " << homeAddress << "] " << message << "\n";
    }

    fclose(file);
}
