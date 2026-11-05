# Laboratory work 3 — Structural design patterns

**Author:** Eftode Andrei, FAF-242

## Objectives

1. Study and understand the structural design patterns.
2. As a continuation of the previous laboratory work, think about the functionalities the
   system needs to provide to the user.
3. Implement some additional functionalities using structural design patterns.

## Used design patterns

- Adapter
- Decorator
- Facade

## The project

Structural patterns are about how classes and objects are put together into bigger
structures. Class patterns do it with inheritance, and object patterns do it with
composition: one object keeps another one inside it and uses it.

The project is the same as in laboratory works 1 and 2: citizens report city problems and
city hall handles them. Lab 3 adds three things the system needs:

- the citizen can be told by **SMS**, through a service bought from a phone company;
- every message city hall sends is **signed**, and city hall keeps a **copy** of it;
- the whole path of a report, from the citizen to the crew, is **one call** to city hall.

Lab 3 uses the classes from lab 1 and lab 2 and does not change them. Every class has its
own pair of files, named after the class: the `.h` declares it and the `.cpp` has the code
of its methods.

| Pattern | Classes | Where they are | What it adds |
| --- | --- | --- | --- |
| Adapter | `SmsGateway`, `SmsNotifier` | [external/](external/), [notifications/](notifications/) | SMS works with the `Notifier` interface from lab 1 |
| Decorator | `NotifierDecorator`, `SignedNotifier`, `ArchivedNotifier` | [notifications/](notifications/) | any notifier can sign its messages and keep a copy of them |
| Facade | `CityHall` | [services/](services/) | one call handles a report from start to end |

The code snippets below show the important parts. In the project, each class is in its
`.h` file and the code of its methods is in the `.cpp` file.

The ready example is the function `runLab3()` in [main.cpp](../main.cpp) (menu option 5).
Option 6, `runLab3Input()`, lets the user choose the console, e-mail or SMS, type as many
reports as they want, and see every message city hall sent at the end.

## 1. Adapter

> It lets classes work together that couldn't otherwise, because of incompatible
> interfaces. Also known as Wrapper.

City hall bought an SMS service from a phone company. The company gives a ready class,
`SmsGateway` ([external/SmsGateway.h](external/SmsGateway.h)). It comes from their library,
so the project can't change it, and its interface does not match `Notifier` from lab 1:

What lab 1 expects:

```cpp
class Notifier {
public:
    virtual void send(const string& message) = 0;
};
```

What the phone company gives:

```cpp
class SmsGateway {
public:
    int sendSms(const char* phoneNumber, const char* text);
};
```

| `Notifier` | `SmsGateway` |
| --- | --- |
| method `send` | method `sendSms` |
| takes a `std::string` | takes C-style text (`const char*`) |
| needs only the message | also needs a phone number |
| shows its own errors | answers with a status code: 0 if it worked, an error code if not |

`SmsNotifier` ([notifications/SmsNotifier.cpp](notifications/SmsNotifier.cpp)) is the
adapter. It **is** a `Notifier`, so anything that works with a `Notifier` can use it. It
**keeps** an `SmsGateway` and the phone number, and turns every `send()` into a call to
`sendSms()`:

```cpp
class SmsNotifier : public Notifier {
public:
    SmsNotifier(SmsGateway* gateway, const string& phoneNumber);

    void send(const string& message) override {
        int status = gateway->sendSms(phoneNumber.c_str(), message.c_str());
        if (status != 0) {
            cout << "[sms] The message could not be sent (error " << status << ").\n";
        }
    }

private:
    SmsGateway* gateway;
    string phoneNumber;
};
```

| Role in the pattern | In the project |
| --- | --- |
| Target, the interface the client expects | `Notifier` (lab 1) |
| Adaptee, the class with the wrong interface | `SmsGateway` |
| Adapter | `SmsNotifier` |
| Client | `ReportService` (lab 1) |

`ReportService` from lab 1 sends SMS without any change, because it only knows `Notifier`:

```cpp
SmsGateway gateway;
SmsNotifier sms(&gateway, "+373 69 123 456");
ReportService smsService(&storage, &validator, &sms);
```

The slides show two kinds of adapter. A **class adapter** inherits from both the target and
the adaptee. An **object adapter** inherits from the target and keeps the adaptee inside
it. `SmsNotifier` is an object adapter, because the gateway comes from outside the project
and keeping it inside is more flexible than inheriting from it: the same adapter can be
given any `SmsGateway` object.

## 2. Decorator

> Add responsibilities to objects dynamically. Wrap the plain object into a specific
> decorator.

City hall wants two more things for every message: a signature, so the citizen knows the
message comes from city hall, and a copy of the message, so city hall can see later what
it told the citizens. Doing it with subclasses would need a class for every mix:
`SignedEmailNotifier`, `SignedSmsNotifier`, `ArchivedSignedSmsNotifier`, and so on. With
three channels and two extras, that is already many classes, and every new channel or
extra would multiply them.

A decorator is a `Notifier` that keeps another `Notifier` inside it. It does its own small
job and passes the message on:

```cpp
class NotifierDecorator : public Notifier {
public:
    explicit NotifierDecorator(Notifier* wrapped);
    void send(const string& message) override { wrapped->send(message); }
private:
    Notifier* wrapped;
};

class SignedNotifier : public NotifierDecorator {
public:
    void send(const string& message) override {
        NotifierDecorator::send(message + " -- Chisinau City Hall");   // adds the signature
    }
};

class ArchivedNotifier : public NotifierDecorator {
public:
    void send(const string& message) override {
        history.push_back(message);            // keeps a copy
        NotifierDecorator::send(message);
    }
    const vector<string>& getHistory() const;
private:
    vector<string> history;
};
```

The files are in [notifications/](notifications/): `NotifierDecorator`, `SignedNotifier` and
`ArchivedNotifier`.

| Role in the pattern | In the project |
| --- | --- |
| Component, the common interface | `Notifier` (lab 1) |
| Concrete Component, the plain object | `ConsoleNotifier`, `EmailNotifier`, `SmsNotifier` |
| Decorator | `NotifierDecorator` |
| Concrete Decorator | `SignedNotifier`, `ArchivedNotifier` |

Because a decorator is a `Notifier` too, decorators can wrap each other, around any
notifier, and the choice is made while the program runs:

```cpp
SignedNotifier signedSms(&sms);              // SMS + signature
ArchivedNotifier archivedSms(&signedSms);    // SMS + signature + copy

EmailNotifier email;
SignedNotifier signedEmail(&email);          // the same signature on e-mail
```

The order matters. `archivedSms` keeps the copy first and the signature is added after, so
the archive has the messages without the signature. Wrapping them the other way around
would keep the signed text.

`ConsoleNotifier`, `EmailNotifier` and `SmsNotifier` were not changed. That is the
Open/Closed Principle from lab 1: the behaviour grows with new classes, and the old ones
stay as they are.

## 3. Facade

> Provides a unified interface that represents multiple components. Wraps a complex
> sub-system with a simple abstraction.

After lab 2, handling one report needed many classes, used in the right order: the rules
and the `Validator`, `ReportService`, the `ReportStorage`, `WorkOrderBuilder`, the right
department, the `TruckPool`. The client (`main.cpp`) had to know all of them. In lab 2,
`runLab2Input()` does every step by hand:

```cpp
ReportService service(&storage, &validator, &notifier);
service.submit(Report(category, description));
WorkOrderBuilder builder(report, address);
...
const Department* department = &roads;
if (category == "Street light") { department = &lighting; } ...
department->handle(order);
```

`CityHall` ([services/CityHall.h](services/CityHall.h)) is the facade. It keeps the parts of
the system inside it and gives the client one method:

```cpp
class CityHall {
public:
    CityHall(ReportStorage* storage, Notifier* notifier);

    bool reportProblem(const string& category, const string& description,
                       const string& address, bool urgent);
    ...
};
```

Behind that one call, `reportProblem()` ([services/CityHall.cpp](services/CityHall.cpp)) does
every step:

```cpp
bool CityHall::reportProblem(const string& category, const string& description,
                             const string& address, bool urgent) {
    // Step 1 (lab 1): check the report, save it and tell the citizen.
    if (!reportService.submit(Report(category, description))) {
        return false;
    }
    vector<Report> reports = storage->all();
    const Report& report = reports.back();

    // Step 2 (lab 2, Builder): make the work order.
    WorkOrderBuilder builder(report, address);
    if (urgent) {
        builder.setPriority("High").setDeadline(2);
    }
    WorkOrder order = builder.build();
    orderPrinter.print(order);

    // Step 3 (lab 2, Object Pool and Factory Method): borrow a truck and send the crew.
    Truck* truck = trucks.acquire();
    ...
    departmentFor(category).handle(order);
    trucks.release(truck);
    return true;
}
```

Now the client needs only this:

```cpp
CityHall cityHall(&storage, &archivedSms);
cityHall.reportProblem("Pothole", "Deep pothole in front of the hospital", "Ismail St. 40", true);
```

| Role in the pattern | In the project |
| --- | --- |
| Facade | `CityHall` |
| Subsystem classes | `Validator` and its rules, `ReportService`, `ReportStorage`, `WorkOrderBuilder`, `WorkOrderPrinter`, the departments, `TruckPool`, `AppConfig` |
| Client | `main.cpp` |

The task asks that the creational patterns are used inside the functionalities instead of
in the client. The facade does that: the Builder, the Factory Method, the Object Pool and
the Singleton from lab 2 are all used inside `CityHall`, and `main.cpp` does not see them.

The facade does not hide the subsystem completely. The classes are still public, so code
that needs something special can still use them directly. City hall also gets the storage
and the notifier from outside, through its constructor, so the client still chooses how the
citizen is told (the Dependency Inversion from lab 1). In the ready example it gets the
signed and archived SMS notifier, so the three patterns of lab 3 work together.

There is only one client for the whole system, `main.cpp`.

## The other structural patterns

The task asks to know the rest of the list too.

| Pattern | What it does | Where it could fit in this project |
| --- | --- | --- |
| Bridge | splits one class hierarchy into two, joined by composition, so both sides can change on their own | messages of different kinds (report accepted, report refused) on one side, and the channels (console, e-mail, SMS) on the other |
| Composite | puts simple and complex objects in a tree, and lets the client treat them the same way | a team of several crews that is used like one `Crew`, for a big job that needs the road crew and the garbage crew together |
| Flyweight | shares the part of many small objects that is the same (intrinsic state), and keeps the part that differs (extrinsic state) outside | the data of a category (its name and its department) shared by thousands of reports, instead of every report keeping its own copy |
| Proxy | puts an object in front of another one, with the same interface, to control the access to it | a notifier that sends a message only during the day, or only to citizens who agreed to get messages |

The project does not need them yet: there are no two dimensions that change on their own,
no tree of objects, not enough reports to save memory, and no access to control.

## Results

```
=== Laboratory work 3: Structural design patterns ===

--- 1. Adapter ---
ReportService from lab 1 gets an SmsNotifier, and its code stays the same:
[sms to +373 69 123 456] Report #1 was registered.
[sms to +373 69 123 456] Report refused: The description must have at least 10 characters.
A phone number that is missing makes SmsGateway return an error code:
[sms] The message could not be sent (error 1).

--- 2. Decorator ---
The SMS notifier, wrapped so every message is signed and kept in the archive:
[sms to +373 69 123 456] Report #2 was registered. -- Chisinau City Hall
The same signature works on any notifier, for example on e-mail:
[e-mail] The street lights on Ion Creanga St. were repaired. -- Chisinau City Hall
The archive kept 1 message(s):
  - Report #2 was registered.

--- 3. Facade ---
[config] The settings were loaded.
An urgent pothole, reported with one call:
[sms to +373 69 123 456] Report #3 was registered. -- Chisinau City Hall
Work order for report #3 (Pothole)
  address:  Ismail St. 40
  priority: High
  deadline: 2 days
Truck #1 goes out. Report #3 (High priority, 2 days): the road crew fills the pothole at Ismail St. 40.

A broken street light that is not urgent:
[sms to +373 69 123 456] Report #4 was registered. -- Chisinau City Hall
Work order for report #4 (Street light)
  address:  Mihai Viteazul St. 7
  priority: Normal
  deadline: 7 days
Truck #1 goes out. Report #4 (Normal priority, 7 days): the electricians repair the street light at Mihai Viteazul St. 7.

A report that is refused does not get a work order:
[sms to +373 69 123 456] Report refused: "Aliens" is not a known category. -- Chisinau City Hall
[sms to +373 69 123 456] Report refused: The description must have at least 10 characters. -- Chisinau City Hall

Every message city hall sent by SMS in this example:
  - Report #2 was registered.
  - Report #3 was registered.
  - Report #4 was registered.
  - Report refused: "Aliens" is not a known category.
  - Report refused: The description must have at least 10 characters.
```

The same truck, #1, goes out both times, because the first job is done and the truck is
back in the pool before the second report comes.

## Conclusions

In this laboratory work I learned that structural patterns are about how classes and
objects are put together. All three patterns I used work by keeping one object inside
another one, instead of writing new subclasses for every case.

The Adapter let me use a class I could not change. The SMS gateway from the phone company
has a different interface, and a small class in between made it look like a normal
`Notifier`. The report service from lab 1 sends SMS without knowing it.

The Decorator let me add a signature and an archive to every kind of message without
touching the notifiers. Each extra is one small class, and the extras can be put one
inside the other in any order and around any notifier, while the program runs.

The Facade made the system easy to use. Before, the client had to know about ten classes
and call them in the right order. Now it calls `reportProblem()`, and city hall does the
steps inside. The creational patterns from lab 2 moved inside city hall too, so the client
does not have to know how the work orders and the crews are made.

The classes from lab 1 and lab 2 did not change. The SMS adapter and the decorators plugged
into the `Notifier` interface from lab 1, so the Dependency Inversion and the Open/Closed
principles from the first lab helped again.

## C++ used in the code

New things compared to lab 1 and lab 2:

| In the code | What it means |
| --- | --- |
| `const char*` | C-style text: a pointer to the first letter of the text. Older libraries use it instead of `std::string` |
| `message.c_str()` | gives the text of a `std::string` as C-style text, so it can be passed to a function that wants `const char*` |
| `strlen(phoneNumber)` | the number of letters in C-style text, from `<cstring>` |
| `SignedNotifier(Notifier* wrapped) : NotifierDecorator(wrapped) {}` | the constructor first calls the constructor of the base class and gives it `wrapped` |
| `NotifierDecorator::send(message)` | calls the method of the base class, not the one of the current class |
| `const vector<string>& getHistory() const` | returns the list itself, not a copy of it, and `const` means the caller can only read it |
| `: storage(storage), reportService(storage, &validator, notifier), trucks(...)` | the initializer list makes the objects that `CityHall` keeps inside it, and it gives them their constructor arguments |
| `const Department& departmentFor(...) const` | returns one of the departments city hall keeps, not a copy, and the caller can't change it |
| `bool urgent = ask("Is it urgent? (y/n): ") == "y";` | the comparison gives `true` or `false`, and it is saved in `urgent` |
