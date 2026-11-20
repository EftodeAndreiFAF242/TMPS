# Laboratory work 3 — Structural design patterns

**Author:** Eftode Andrei, FAF-242

The report is in **[REPORT.md](REPORT.md)**.

Lab 3 adds four structural patterns to the city reports project from labs 1 and 2:

- **Adapter**: `SystemCalendar` gives the real date of every work order with the time functions of the C standard library (`<ctime>`);
- **Decorator**: `SignedNotifier` and `ArchivedNotifier` sign every message and keep a copy of it;
- **Composite**: `CrewTeam` is a team of crews, sent by `StormDepartment` the same way as one crew;
- **Facade**: `CityHall` handles a report from start to end with one call.

## Build and run

From the project folder (the one with `CMakeLists.txt`), with CMake:

```
cmake -S . -B build
cmake --build build
./build/tmps
```

or with g++ only, from Git Bash:

```
g++ -std=c++17 -I. main.cpp Lab1/*/*.cpp Lab2/*/*.cpp Lab3/*/*.cpp -o tmps
./tmps
```

In the menu, option **5** runs the ready example of lab 3, one section per pattern, and
option **6** lets you type your own reports and choose how the citizen is told (console or
e-mail). The known categories are Pothole, Street light, Garbage and Storm damage.

## Run the unit tests

One command, with g++ (from Git Bash):

```
g++ -std=c++17 -I. tests/Lab3Tests.cpp Lab1/*/*.cpp Lab2/*/*.cpp Lab3/*/*.cpp -o lab3_tests && ./lab3_tests
```

or, after the CMake build above:

```
ctest --test-dir build --output-on-failure
```

The tests are a plain C++ program, without a test framework: 17 tests, at least three for
each pattern. It prints `[PASS]` or `[FAIL]` for every test and returns 0 when all of them pass.

## Files

```
Lab3/
  README.md                how to build, run and test lab 3 (this file)
  REPORT.md                the report
  calendar/
    Calendar               Adapter: the Target, the dates the project needs
    SystemCalendar         Adapter: Calendar -> the C library's localtime, mktime, strftime
  notifications/
    NotifierDecorator      Decorator: the base class of every notifier that wraps another one
    SignedNotifier         Concrete Decorator: adds the city hall signature
    ArchivedNotifier       Concrete Decorator: keeps a copy of every message
    MessageArchive         the list ArchivedNotifier writes the copies into
  crews/
    CrewTeam               Composite: a team of crews that works like one crew
  departments/
    StormDepartment        a Factory Method creator (lab 2) that makes a CrewTeam
  validation/
    KnownCategoryRule      knows the categories from the departments of city hall
  services/
    CityHall               Facade: one entry point for everything city hall does with a report
tests/
  Lab3Tests.cpp            the unit tests of lab 3
main.cpp                   the client: runLab3() and runLab3Input()
```
