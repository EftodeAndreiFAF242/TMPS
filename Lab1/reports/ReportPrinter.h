#pragma once

struct Report;

// Shows a report on the screen.
class ReportPrinter {
public:
    void print(const Report& report);
};
