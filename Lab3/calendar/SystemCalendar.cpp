// "It lets classes work together, that couldn't otherwise because of incompatible parent classes."
// Lab 3 - Adapter: the Adapter, gives the dates of Calendar with the time functions of the C library

#include "Lab3/calendar/SystemCalendar.h"

using namespace std;

SystemCalendar::SystemCalendar(time_t today) {
    this->today = today;
}

string SystemCalendar::dateIn(int days) const {
    // Despărțim timpul în zi, lună, an
    tm* parts = localtime(&today);
    if (parts == nullptr) {
        return "unknown date";
    }
    tm date = *parts;

    // Add the days, mktime fixes them
    date.tm_mday += days;
    if (mktime(&date) == -1) {
        return "unknown date";
    }

    // Write the date into a buffer
    char text[11];
    if (strftime(text, sizeof(text), "%d.%m.%Y", &date) == 0) {
        return "unknown date";
    }
    return string(text);
}
