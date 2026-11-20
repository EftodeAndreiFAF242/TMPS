// Lab 3 - Adapter: the Adapter, gives the dates of Calendar with the time functions of the C library

#include "Lab3/calendar/SystemCalendar.h"

using namespace std;

SystemCalendar::SystemCalendar(time_t today) {
    this->today = today;
}

string SystemCalendar::dateIn(int days) const {
    // Calendar has one call, and the C library needs three: split the time into a date, move the
    // date, and write it as text. localtime gives a pointer to a struct tm that the C library
    // shares with everyone, or nullptr when it fails, so the adapter checks it and copies it.
    tm* parts = localtime(&today);
    if (parts == nullptr) {
        return "unknown date";
    }
    tm date = *parts;

    // The C library has no "add days". The days are added to the day of the month, and mktime
    // turns an impossible date, like 32 November, into the right one, 2 December.
    date.tm_mday += days;
    if (mktime(&date) == -1) {
        return "unknown date";
    }

    // strftime writes C-style text into a buffer we give it, and returns 0 when the text does not
    // fit. "22.11.2026" has 10 characters, plus the zero that ends C-style text.
    char text[11];
    if (strftime(text, sizeof(text), "%d.%m.%Y", &date) == 0) {
        return "unknown date";
    }
    return string(text);
}
