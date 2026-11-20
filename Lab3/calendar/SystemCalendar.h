// Lab 3 - Adapter: the Adapter, gives the dates of Calendar with the time functions of the C library

#pragma once

#include <ctime>
#include <string>

#include "Lab3/calendar/Calendar.h"

// The dates come from the C standard library (<ctime>), which the project did not write and can't
// change. Its interface does not match Calendar: it counts seconds since 1970 (time_t), splits a
// date into a struct tm where the months start at 0 and the years at 1900, has no "add days"
// (mktime has to fix the day of the month), writes C-style text into a buffer we give it
// (strftime), and answers with error codes.
class SystemCalendar : public Calendar {
public:
    // today: the moment the days are counted from. main gives the real time, the tests a fixed day.
    explicit SystemCalendar(std::time_t today);

    std::string dateIn(int days) const override;

private:
    std::time_t today;
};
