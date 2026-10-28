# TMPS — Laboratory Works

- **Course:** Software Design Techniques and Mechanisms (TMPS)
- **Author:** Eftode Andrei, FAF-242
- **Professor:** Istrati D.

One small application grows through the semester: the backend of a system where citizens
report city problems (a pothole, a broken street light, dumped garbage) and city hall
handles them. It has no graphical interface on purpose, because the course is about how
the code is designed.

Each laboratory work has its own folder, with its own report.

| Laboratory work | Topic | Folder |
| --- | --- | --- |
| 1 | SOLID principles | [Lab1](Lab1/) |
| 2 | Creational design patterns | [Lab2](Lab2/) |

## How to run

The project needs only a C++ compiler (g++).

```
g++ -I. main.cpp Lab1/*.cpp Lab2/*.cpp -o tmps
./tmps
```

`-I.` tells g++ that include paths start at the project folder, and `Lab1/*.cpp Lab2/*.cpp`
compiles the code of every class together with `main.cpp`. Building only `main.cpp` is not
enough, because the code of the methods is in the other `.cpp` files.

The program shows a menu. Each laboratory work can run in two ways:

- **the ready example**: the data is already written in the code, so every case is shown;
- **your own data**: you type the reports in the console, and the same classes handle them.

Type `0` to exit.

## Files

```
main.cpp    the menu, the ready example of each laboratory work and the version with your own data
Lab1/       laboratory work 1: a .h and a .cpp for each SOLID principle
Lab2/       laboratory work 2: a .h and a .cpp for each creational pattern
```

## How the code is organized

Each part of a laboratory work comes in two files:

- the `.h` file (the header) **declares** the classes: their names, fields and methods,
  without the code of the methods;
- the `.cpp` file has the **code** of those methods.

`#include` copies the whole text of a file into the place where it is written. A header
has only declarations, so a file that includes it gets a short text, and each `.cpp` file
is compiled on its own.

Every file follows these rules:

| Rule | Example |
| --- | --- |
| A file includes everything it uses itself, and does not count on another header to bring it in | `Builder.h` includes `<string>`, because `WorkOrder` has `std::string` fields |
| Include paths start at the project folder | `#include "Lab1/SingleResponsibility.h"` in any folder, never `"../Lab1/..."` |
| A header that uses a class only through a pointer or a reference declares the class instead of including its file | `struct Report;` in `Builder.h`, and the full `#include` only in `Builder.cpp` |
| A class kept inside another one by value needs its full header | `Singleton.h` includes `SingleResponsibility.h`, because `Database` keeps a whole `ReportStorage` inside it |
| Headers write `std::string` and `std::vector`, and only `.cpp` files have `using namespace std;` | a `using` in a header would reach every file that includes it |
| The includes come in groups: the file's own header, then the standard library, then the files of the project | `Builder.cpp` |
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
