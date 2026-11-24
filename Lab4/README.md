# Laboratory work 4 — Behavioral design patterns

**Author:** Eftode Andrei, FAF-242

The report is in **[REPORT.md](REPORT.md)**.

Lab 4 adds four behavioral patterns to the city reports project from labs 1, 2 and 3. They
follow every report after the crew goes out, until the case is closed:

- **State**: `ReportCase` moves through `RegisteredState`, `InProgressState`, `FixedState` and `ClosedState`, and each status decides which step is allowed;
- **Observer**: `CitizenUpdates` (an e-mail, signed and archived by the decorators of lab 3) and `CaseLog` (with the date from the adapter of lab 3) are told about every change;
- **Memento**: `CaseSnapshot` is a saved copy of a case that only the case can read;
- **Command**: the operator's steps are command objects run by `OperatorDesk`, which keeps them and can undo them.

## Build and run

From the project folder (the one with `CMakeLists.txt`), with CMake:

```
cmake -S . -B build
cmake --build build
./build/tmps
```

or with g++ only, from Git Bash:

```
g++ -std=c++17 -I. main.cpp Lab1/*/*.cpp Lab2/*/*.cpp Lab3/*/*.cpp Lab4/*/*.cpp -o tmps
./tmps
```

In the menu, option **7** runs the ready example of lab 4, one section per pattern (the last
section shows all four together), and option **8** lets you type your own report and then give
the operator's commands yourself: start the work, finish it, close or reopen the case, undo the
last command, and stop or start the updates to the citizen.

## Run the unit tests

One command, with g++ (from Git Bash):

```
g++ -std=c++17 -I. tests/Lab4Tests.cpp Lab1/*/*.cpp Lab2/*/*.cpp Lab3/*/*.cpp Lab4/*/*.cpp -o lab4_tests && ./lab4_tests
```

or, after the CMake build above (this runs the tests of lab 3 too):

```
ctest --test-dir build --output-on-failure
```

The tests are a plain C++ program, without a test framework: 21 tests, at least four for each
pattern and two for all four together. It prints `[PASS]` or `[FAIL]` for every test and
returns 0 when all of them pass.

## Files

```
Lab4/
  README.md                how to build, run and test lab 4 (this file)
  REPORT.md                the report
  cases/
    ReportCase             State: the Context (also Observer's Subject and Memento's Originator)
    CaseSnapshot           Memento: a saved copy of a case, only ReportCase can read it
  statuses/
    ReportState            State: the State, every step is refused unless a status allows it
    RegisteredState        Concrete State: the report is saved and waits for a crew
    InProgressState        Concrete State: the crew is working
    FixedState             Concrete State: the crew finished, the citizen can check
    ClosedState            Concrete State: the case is over, every step is refused
  updates/
    CaseObserver           Observer: the Observer interface
    CitizenUpdates         Concrete Observer: tells the citizen through any Notifier
    CaseLog                Concrete Observer: the city hall log, with the date from Calendar
  operator/
    Command                Command: the Command interface (execute, undo)
    StartWorkCommand       Concrete Command: the crew starts the work
    FinishWorkCommand      Concrete Command: the crew finished
    CloseCaseCommand       Concrete Command: the citizen confirmed, the case is closed
    ReopenCaseCommand      Concrete Command: the problem is still there
    OperatorDesk           Invoker: runs the commands, keeps the history, undoes the newest
tests/
  Lab4Tests.cpp            the unit tests of lab 4
main.cpp                   the client: runLab4() and runLab4Input()
```
