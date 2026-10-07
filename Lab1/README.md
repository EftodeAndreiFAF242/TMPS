# Laboratory work 1 — SOLID principles

**Author:** Eftode Andrei, FAF-242

## Objectives

1. Study the SOLID principles.
2. Choose a domain and start a project in it.
3. Implement three SOLID principles in the project.

## The project

The application takes reports about city problems. At this stage it does three things
with a report: it checks it, it saves it, and it tells the citizen what happened. This is
the base the next laboratory works build on.

Each principle has its own file:

| File | Principle | Classes in it |
| --- | --- | --- |
| [SingleResponsibility.hpp](SingleResponsibility.hpp) | Single Responsibility (SRP) | `Report`, `ReportStorage`, `ReportPrinter` |
| [OpenClosed.hpp](OpenClosed.hpp) | Open/Closed (OCP) | `Rule`, `CategoryRule`, `DescriptionRule`, `Validator` |
| [DependencyInversion.hpp](DependencyInversion.hpp) | Dependency Inversion (DIP) | `Notifier`, `ConsoleNotifier`, `EmailNotifier`, `ReportService` |

The demo is the function `runLab1()` in [main.cpp](../main.cpp).

## 1. Single Responsibility Principle

> A class should have only one reason to change.

There are three classes and each one has one job:

| Class | Its job | When it has to change |
| --- | --- | --- |
| `Report` | holds the data of one report | a report gets a new field |
| `ReportStorage` | keeps the reports | the reports move to a file or a database |
| `ReportPrinter` | shows a report on the screen | the text on the screen changes |

`Report` has no `save()` and no `print()`. If it had them, a change to the storage or to
the text on the screen would mean editing `Report`, and it could break the other two jobs.

```cpp
struct Report {
    int id;
    string category;
    string description;
    // only a constructor, no save() and no print()
};

class ReportStorage {
public:
    int add(Report report);    // saves a report and gives it an id
    vector<Report> all();      // returns every saved report
};

class ReportPrinter {
public:
    void print(const Report& report);
};
```

## 2. Open/Closed Principle

> Code should be open for extension and closed for modification.

`Rule` is an interface with one method. Every validation rule is a class that inherits
from it:

```cpp
class Rule {
public:
    virtual ~Rule() {}
    virtual string check(const Report& report) = 0;   // "" if fine, or the error message
};
```

The `Validator` keeps a list of rules and runs all of them. It never asks which rule it
is running:

```cpp
for (Rule* rule : rules) {
    string error = rule->check(report);
    if (error != "") {
        errors.push_back(error);
    }
}
```

To add a rule, a new class is written and given to the validator with `addRule`. The
`Validator` class and the old rules are not edited. That is the principle: the behaviour
grows (open for extension) and the existing code stays as it is (closed for modification).

The demo shows it. The same report is checked twice, first with one rule and then with
two. The second check finds one more error, and the code of `Validator` is the same both
times.

## 3. Dependency Inversion Principle

> High-level code should not depend on low-level details. Both should depend on an
> abstraction.

`ReportService` is the high-level code. It holds the steps for a new report: check it,
save it, tell the citizen. The way the message reaches the citizen is a low-level detail.

Between them stands the `Notifier` interface:

```cpp
class Notifier {
public:
    virtual ~Notifier() {}
    virtual void send(const string& message) = 0;
};
```

The service keeps a pointer to a `Notifier` and receives it through its constructor. The
names `ConsoleNotifier` and `EmailNotifier` do not appear anywhere in `ReportService`:

```cpp
ReportService(ReportStorage* storage, Validator* validator, Notifier* notifier)
```

The real notifier is chosen in `main.cpp`, outside the service:

```cpp
ReportService service(&storage, &validator, &consoleNotifier);
ReportService emailService(&storage, &validator, &emailNotifier);
```

Both lines use the same class. Only the notifier that is passed in differs, so moving from
the console to e-mail needs no change in `ReportService`.

The principle is applied to the notifier. `ReportStorage` and `Validator` are also given
to the service from outside, but they are still concrete classes. If the reports move to
a file later, the storage gets an interface in the same way.

## Results

```
=== Laboratory work 1: SOLID principles ===

--- 1. Single Responsibility Principle ---
#1 [Pothole] Deep pothole near the bus stop
#2 [Garbage] Garbage left next to the playground

--- 2. Open/Closed Principle ---
A report with the category "Aliens" and the description "Help", checked with 1 rule:
  - "Aliens" is not a known category.
The same report, checked with 2 rules:
  - "Aliens" is not a known category.
  - The description must have at least 10 characters.

--- 3. Dependency Inversion Principle ---
The service with the console notifier:
[console] Report #3 was registered.
[console] Report refused: "Aliens" is not a known category.
[console] Report refused: The description must have at least 10 characters.
The same service class with the e-mail notifier:
[e-mail] Report #4 was registered.

Every report in the storage:
#1 [Pothole] Deep pothole near the bus stop
#2 [Garbage] Garbage left next to the playground
#3 [Street light] The street light has been off for a week
#4 [Pothole] The road is broken in front of the school
```

## Conclusions

The three principles answer the same question: what is likely to change, and how to keep
it apart from the rest.

- SRP split the program into small classes, so a change to the storage does not touch the
  printing.
- OCP made validation rules something that is added, not edited.
- DIP made the service independent of the way a message is delivered.

The price is a few more classes than the program strictly needs at this size. In return,
the next laboratory works can add to this code without rewriting it.

## C++ used in the code

| In the code | What it means |
| --- | --- |
| `#pragma once` | include this file only once, even if several files ask for it |
| `this->id = 0;` | `this->id` is the field of the object, and it is set in the constructor |
| `virtual string check(...) = 0;` | a method without a body; every class that inherits has to write it. A class with such a method is an interface |
| `override` | this method replaces the one from the base class; the compiler checks that the names match |
| `virtual ~Rule() {}` | a virtual destructor, needed in any base class that has virtual methods |
| `const Report& report` | the report is passed without being copied, and the method promises not to change it |
| `Rule*` | a pointer to a rule. A `Rule*` can point to a `CategoryRule` or to any other rule |
| `&categoryRule` | the address of the object, which is what a pointer stores |
| `rule->check(report)` | calls a method through a pointer |
| `for (Rule* rule : rules)` | goes through every element of the vector |
| `to_string(id)` | turns a number into text |
