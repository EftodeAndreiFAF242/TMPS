# TMPS — Laboratory Works

- **Course:** Software Design Techniques and Mechanisms (TMPS)
- **Author:** Eftode Andrei, FAF-242
- **Professor:** Istrati D.

One small application grows through the semester: the backend of a system where citizens
report city problems (a pothole, a broken street light, dumped garbage) and city hall
handles them. It has no graphical interface on purpose, because the course is about how
the code is designed.

Each laboratory work has its own folder, with the classes it added and its report. Inside
a lab folder the code is organized like a company project: the folders are named after what
the code does (reports, validation, work orders, ...), and every class has its own files,
named after the class.

| Laboratory work | Topic | Folder |
| --- | --- | --- |
| 1 | SOLID principles | [Lab1](Lab1/) |
| 2 | Creational design patterns | [Lab2](Lab2/) |

## How to run

The project needs a C++ compiler (g++) and CMake.

```
cmake -S . -B build
cmake --build build
./build/tmps
```

`CMakeLists.txt` finds every `.cpp` file in `Lab1/` and `Lab2/` by itself, so a new class
needs no change in the build.

Without CMake, from Git Bash:

```
g++ -std=c++17 -I. main.cpp Lab1/*/*.cpp Lab2/*/*.cpp -o tmps
./tmps
```

`-I.` tells g++ that include paths start at the project folder, and `Lab1/*/*.cpp
Lab2/*/*.cpp` compiles the code of every class together with `main.cpp`. Building only
`main.cpp` is not enough, because the code of the methods is in the other `.cpp` files.
PowerShell does not expand `Lab1/*/*.cpp`, so in PowerShell use CMake.

The program shows a menu. Each laboratory work can run in two ways:

- **the ready example**: the data is already written in the code, so every case is shown;
- **your own data**: you type the reports in the console, and the same classes handle them.

Type `0` to exit.

## Files

```
CMakeLists.txt      how the program is built
main.cpp            the menu, the ready example of each laboratory work and the version with your own data
Lab1/               laboratory work 1: SOLID principles
  README.md         the report
  reports/          a report and what happens to it: Report, ReportPrinter, ReportService
  storage/          where the reports are kept: ReportStorage
  validation/       the checks a report has to pass: Rule, CategoryRule, DescriptionRule, Validator
  notifications/    how the citizen is told: Notifier, ConsoleNotifier, EmailNotifier
Lab2/               laboratory work 2: creational design patterns
  README.md         the report
  config/           the settings of the application: AppConfig
  workorders/       the task made for a report: WorkOrder, WorkOrderBuilder, WorkOrderPrinter
  departments/      the departments of city hall: Department, RoadDepartment, LightingDepartment, SanitationDepartment
  crews/            the crews that do the work: Crew, RoadCrew, ElectricianCrew, GarbageCrew, GreenSpacesCrew
  fleet/            the trucks of city hall: Truck, TruckPool
quiz_lab1_2/        a quiz to study for labs 1 and 2
```

## How the code is organized

Every class has its own two files, named after the class:

- the `.h` file (the header) **declares** the class: its name, fields and methods, without
  the code of the methods;
- the `.cpp` file has the **code** of those methods.

An interface (a class where every method is `= 0`) and a struct without methods have only
a `.h` file, because there is no code to put in a `.cpp`: `Rule.h`, `Notifier.h`, `Crew.h`
and `WorkOrder.h`.

`#include` copies the whole text of a file into the place where it is written. A header
has only declarations, so a file that includes it gets a short text, and each `.cpp` file
is compiled on its own.

Every file follows these rules:

| Rule | Example |
| --- | --- |
| A file is named after the class it holds | `class WorkOrderBuilder` is in `WorkOrderBuilder.h` and `WorkOrderBuilder.cpp` |
| A file includes everything it uses itself, and does not count on another header to bring it in | `WorkOrder.h` includes `<string>`, because `WorkOrder` has `std::string` fields |
| Include paths start at the project folder | `#include "Lab1/reports/Report.h"` in any folder, never `"../reports/Report.h"` |
| A header that uses a class only through a pointer or a reference declares the class instead of including its file | `struct Report;` in `WorkOrderBuilder.h`, and the full `#include` only in `WorkOrderBuilder.cpp` |
| A class kept inside another one by value needs its full header | `WorkOrderBuilder.h` includes `WorkOrder.h`, because `WorkOrderBuilder` keeps a whole `WorkOrder` inside it |
| Lab 2 can use the classes of lab 1, but lab 1 never includes anything from lab 2 | `WorkOrderBuilder.cpp` includes `Lab1/reports/Report.h` |
| Headers write `std::string` and `std::vector`, and only `.cpp` files have `using namespace std;` | a `using` in a header would reach every file that includes it |
| The includes come in groups: the file's own header, then the standard library, then the files of the project | `ReportService.cpp` |
| Every header starts with `#pragma once` | a header included twice is read only once |

In a `.cpp` file, the name of the class comes before the method, joined by `::`:

```cpp
WorkOrderBuilder& WorkOrderBuilder::setDeadline(int days) {
    order.deadlineDays = days;
    return *this;
}
```

`WorkOrderBuilder::` says that this is the code of the method `setDeadline` that was
declared in the class `WorkOrderBuilder`.
