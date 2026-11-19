# Laboratory work 3 — Structural design patterns

**Author:** Eftode Andrei, FAF-242

On ELSE: *Laboratory work #2 — Structural Design Patterns*. The report is in
**[REPORT.md](REPORT.md)**.

Lab 3 adds three structural patterns to the city reports project from labs 1 and 2:

- **Adapter**: `LetterNotifier` writes paper letters with the C standard library (`<cstdio>`);
- **Decorator**: `SignedNotifier` and `ArchivedNotifier` sign every message and keep a copy of it;
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

In the menu, option **5** runs the ready example of lab 3, and option **6** lets you type
your own reports and choose how the citizen is told (console, e-mail or paper letter). The
letters are written into `letters.txt`, in the folder the program runs from.

## Run the unit tests

One command, with g++ (from Git Bash):

```
g++ -std=c++17 -I. tests/Lab3Tests.cpp Lab1/*/*.cpp Lab2/*/*.cpp Lab3/*/*.cpp -o lab3_tests && ./lab3_tests
```

or, after the CMake build above:

```
ctest --test-dir build --output-on-failure
```

The tests are a plain C++ program, without a test framework: 12 tests, at least two for each
pattern. It prints `[PASS]` or `[FAIL]` for every test and returns 0 when all of them pass.

## Files

```
Lab3/
  README.md                how to build, run and test lab 3 (this file)
  REPORT.md                the report
  notifications/
    LetterNotifier         Adapter: Notifier -> the C library's fopen, fputs, fclose
    NotifierDecorator      Decorator: the base class of every notifier that wraps another one
    SignedNotifier         Concrete Decorator: adds the city hall signature
    ArchivedNotifier       Concrete Decorator: keeps a copy of every message
  services/
    CityHall               Facade: one entry point for everything city hall does with a report
tests/
  Lab3Tests.cpp            the unit tests of lab 3
main.cpp                   the client: runLab3() and runLab3Input()
```
