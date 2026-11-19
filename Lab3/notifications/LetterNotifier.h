// Lab 3 - Adapter: the Adapter, lets any code that uses Notifier write paper letters with the C library

#pragma once

#include <string>

#include "Lab1/notifications/Notifier.h"

// Some citizens have no phone and no e-mail, so city hall sends them a paper letter. The letters
// are written into a text file that the post office prints. The file is written with the C
// standard library (fopen, fputs and fclose from <cstdio>), which the project did not write and
// can't change. Its interface does not match Notifier: it works with a FILE* that has to be opened
// and closed, it takes C-style text, and it answers with error codes.
class LetterNotifier : public Notifier {
public:
    LetterNotifier(const std::string& fileName, const std::string& homeAddress);

    void send(const std::string& message) override;

private:
    std::string fileName;     // the file the post office prints, fopen needs it
    std::string homeAddress;  // a letter needs it, but Notifier::send() does not have it
};
