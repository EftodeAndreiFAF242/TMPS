// Lab 1 - Single Responsibility Principle (SRP): only shows a report on the screen

#pragma once

struct Report;

// Shows a report on the screen.
class ReportPrinter {
public:
    void print(const Report& report);
};
