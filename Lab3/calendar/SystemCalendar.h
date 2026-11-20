// Lab 3 - Adapter: the Adapter, gives the dates of Calendar with the time functions of the C library

#pragma once

#include <ctime>
#include <string>

#include "Lab3/calendar/Calendar.h"

// Datele vin din biblioteca C <ctime>
class SystemCalendar : public Calendar {
public:
    // The day we count from
    explicit SystemCalendar(std::time_t today);

    std::string dateIn(int days) const override;

private:
    std::time_t today;
};
