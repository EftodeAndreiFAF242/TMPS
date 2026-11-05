# Laboratory work 2 — Creational design patterns

**Author:** Eftode Andrei, FAF-242

## Objectives

1. Study the creational design patterns.
2. Decide how the objects of the project are created.
3. Implement three creational design patterns in the project.

## The project

Creational patterns are about how objects are made: who makes them, when, and how many.

The project is the same as in laboratory work 1: citizens report city problems and city
hall handles them. Lab 2 adds the next step. After a report is accepted, city hall makes
a work order for it, and the department in charge sends a repair crew.

Lab 2 uses the classes from lab 1 (`Report`, `ReportStorage`, `Validator`,
`ReportService`, `ConsoleNotifier`) and does not change them. Every class has its own pair
of files, named after the class: the `.h` declares it and the `.cpp` has the code of its
methods. The interface `Crew` and the struct `WorkOrder` have only a `.h`.

| Pattern | Classes | Where they are | What it decides about making objects |
| --- | --- | --- | --- |
| Singleton | `AppConfig` | [config/](config/) | there is only one set of settings |
| Builder | `WorkOrder`, `WorkOrderBuilder`, `WorkOrderPrinter` | [workorders/](workorders/) | a work order is made step by step |
| Factory Method | `Department` and 3 departments, `Crew` and its crews | [departments/](departments/), [crews/](crews/) | each department chooses which crew it makes |
| Object Pool (extra) | `Truck`, `TruckPool` | [fleet/](fleet/) | trucks are made once and reused |

The code snippets below show a class and the code of its methods together, so they can be
read in one place. In the project, the class is in the `.h` file and the code of its
methods is in the `.cpp` file.

The ready example is the function `runLab2()` in [main.cpp](../main.cpp) (menu option 3).
Option 4, `runLab2Input()`, takes one report typed in the console all the way through: it is
saved in the storage, the user gives the parts of the work order (and can skip the optional
ones), and the department for its category sends a crew.

## 1. Singleton

> A class has only one object, and the whole program reaches it from one place.

The application has settings: the priority and the deadline a work order gets when nobody
gives them, and how many trucks city hall has. There must be only one set of settings. If
two parts of the program each had their own copy, they could disagree, for example one part
could think city hall has 2 trucks and another one 3. So the settings live in `AppConfig`,
and the program can't make a second `AppConfig`.

```cpp
class AppConfig {
public:
    static const AppConfig& getInstance() {
        static AppConfig instance;   // made at the first call, then the same object every time
        return instance;
    }

    AppConfig(const AppConfig&) = delete;              // no copies
    AppConfig& operator=(const AppConfig&) = delete;

    const string& getDefaultPriority() const;   // "Normal"
    int getDefaultDeadlineDays() const;         // 7
    int getTruckCount() const;                  // 2

private:
    AppConfig() { ... }   // private: only getInstance() can make an AppConfig
    string defaultPriority;
    int defaultDeadlineDays;
    int truckCount;
};
```

Three things together make sure there is only one set of settings:

| In the code | What it stops |
| --- | --- |
| private constructor | `AppConfig config;` written anywhere outside the class does not compile |
| `= delete` on the copy | `AppConfig copy = AppConfig::getInstance();` does not compile |
| `static AppConfig instance;` | `getInstance()` makes the object only at the first call and returns it after that |

The settings are made the first time someone asks for them, not when the program starts.
The C++ standard also guarantees that two threads calling `getInstance()` at the same
moment still get only one `AppConfig`.

`getInstance()` returns a `const` reference and the class has only getters, so nobody can
change the settings after they are made. That is why it is safe to read them from anywhere:
`main.cpp` reads the number of trucks, and `WorkOrderBuilder` reads the default priority and
deadline. A singleton that anybody could change would be a global variable, and a change
made in one place could break another.

The demo asks for the settings twice, as `first` and `second`. The message
`The settings were loaded.` appears once, and the two have the same address in memory.
Running lab 2 a second time from the menu shows the same thing: the settings are not made
again.

For now the values are written in the constructor. Later they can be read from a file, and
only the constructor of `AppConfig` will change.

### Why the database is not a singleton

In the first version the singleton was a `Database` that kept the reports. A database is a
bad fit for a singleton:

- a real application can need more than one database, for example a test database next to
  the real one, while it always has exactly one set of settings;
- the reports change all the time, and when anybody can reach shared data from anywhere and
  change it, it is hard to know who changed it. The settings are only read, so this problem
  does not exist for them.

Now the reports are kept in a normal `ReportStorage` from lab 1. `main()` makes it once and
gives it to the functions that need it, the same way `ReportService` gets its storage
through its constructor (the Dependency Inversion from lab 1):

```cpp
int main() {
    ReportStorage storage;   // one storage for the whole run of the program
    ...
    runLab2(storage);
}

void runLab2(ReportStorage& storage) {
    ReportService service(&storage, &validator, &notifier);
    ...
}
```

There is still only one storage, and the reports from the first run of lab 2 are still in
it the second time, but now the code that uses it shows where it comes from.

## 2. Builder

> Build a complex object step by step, giving only the parts that are needed.

A work order has six parts. Three are needed every time (the id of the report, its
category and the address) and three are optional (the priority, the deadline and a note):

```cpp
struct WorkOrder {
    int reportId = 0;
    string problem;
    string address;
    string priority;
    int deadlineDays = 0;
    string note;
};
```

Without a builder it would be made with a constructor like this:

```cpp
WorkOrder(1, "Pothole", "Stefan cel Mare Blvd. 12", "High", 2, "Put up a sign first")
```

The call is hard to read: nothing says which number is the id and which one is the
deadline, and swapping them still compiles. Every mix of optional parts would also need
one more constructor.

`WorkOrderBuilder` asks for the needed parts in its constructor, so a work order without
an address can't be built. The optional parts each have their own method, and `build()`
returns the finished order:

```cpp
WorkOrder potholeOrder = WorkOrderBuilder(reports[0], "Stefan cel Mare Blvd. 12")
                             .setPriority("High")
                             .setDeadline(2)
                             .setNote("Children cross here, put up a warning sign first")
                             .build();

WorkOrder garbageOrder = WorkOrderBuilder(reports[2], "Valea Morilor park").build();
```

Every value has a name next to it. The parts that are not given keep the default values
that the builder takes from the settings when it is made:

```cpp
WorkOrderBuilder(const Report& report, const string& address) {
    order.reportId = report.id;
    order.problem = report.category;
    order.address = address;

    const AppConfig& config = AppConfig::getInstance();
    order.priority = config.getDefaultPriority();          // "Normal"
    order.deadlineDays = config.getDefaultDeadlineDays();  // 7
}
```

The calls can follow each other because every method returns the builder itself:

```cpp
WorkOrderBuilder& setPriority(const string& priority) {
    order.priority = priority;
    return *this;
}
```

The demo builds three work orders: one with every optional part, one with only the
deadline, and one with none.

The book version of the pattern also has a Director, a class that keeps ready-made
recipes like "an urgent order". The project doesn't need any recipes yet, so there is no
Director.

## 3. Factory Method

> The base class says when an object is made. Each subclass decides which class it is.

Every department handles a work order the same way: it forms a crew and the crew does the
job. Only the kind of crew is different.

| Creator (`Department`) | Product it makes (`Crew`) |
| --- | --- |
| `RoadDepartment` | `RoadCrew` |
| `LightingDepartment` | `ElectricianCrew` |
| `SanitationDepartment` | `GarbageCrew` |

`Department` writes the common steps once, in `handle()`. The one step that differs is the
factory method `createCrew()`, which has no body in `Department`:

```cpp
class Department {
public:
    virtual unique_ptr<Crew> createCrew() const = 0;   // the factory method

    void handle(const WorkOrder& order) const {
        unique_ptr<Crew> crew = createCrew();   // the subclass decides which crew this is
        crew->work(order);
    }
};

class RoadDepartment : public Department {
public:
    unique_ptr<Crew> createCrew() const override {
        return make_unique<RoadCrew>();
    }
};
```

`handle()` knows only the `Crew` interface. The names `RoadCrew`, `ElectricianCrew` and
`GarbageCrew` appear only in the department that makes them. A new department, for
example one for parks, is one new subclass with its own `createCrew()`. `Department` and
the other departments are not edited, which is the Open/Closed Principle from lab 1.

The crew has to outlive `createCrew()`, so it is made on the heap with `make_unique` and
returned inside a `unique_ptr`, a pointer that owns its object. When `crew` goes out of
scope at the end of `handle()`, the `unique_ptr` deletes the crew by itself, so there is
no `delete` to forget. `Crew` has a virtual destructor, so the right kind of crew is
destroyed.

## 4. Object Pool (extra)

> Keep a few ready objects and lend them out, instead of making a new one every time.

The task does not require this pattern. City hall has a fixed number of trucks. A crew
borrows one for a job, gives it back when the job is done, and the next crew gets that
same truck.

```cpp
class TruckPool {
public:
    explicit TruckPool(int size); // makes every truck, once
    Truck* acquire();             // lends a free truck, or nullptr if all are in use
    void release(Truck* truck);   // takes a truck back
private:
    vector<Truck> trucks;
};
```

In the demo, the pool has 2 trucks (the number comes from the settings) and 3 crews need
one. The third crew gets `nullptr`
and waits. When the road crew gives truck #1 back, the garbage crew gets truck #1, the
same object, which was not made again.

In real programs the pool holds objects that are slow to make or that there are only a
few of, like connections to a database.

## Results

```
=== Laboratory work 2: Creational design patterns ===

--- 1. Singleton ---
[config] The settings were loaded.
Both calls returned the same settings.
The settings of the application:
  default priority: Normal
  default deadline: 7 days
  trucks:           2

--- 2. Builder ---
[console] Report #1 was registered.
[console] Report #2 was registered.
[console] Report #3 was registered.
Work order for report #1 (Pothole)
  address:  Stefan cel Mare Blvd. 12
  priority: High
  deadline: 2 days
  note:     Children cross here, put up a warning sign first
Work order for report #2 (Street light)
  address:  Dacia Blvd. 5
  priority: Normal
  deadline: 3 days
Work order for report #3 (Garbage)
  address:  Valea Morilor park
  priority: Normal
  deadline: 7 days

--- 3. Factory Method ---
Report #1 (High priority, 2 days): the road crew fills the pothole at Stefan cel Mare Blvd. 12.
Report #2 (Normal priority, 3 days): the electricians repair the street light at Dacia Blvd. 5.
Report #3 (Normal priority, 7 days): the garbage crew cleans up at Valea Morilor park.

--- 4. Object Pool (extra) ---
City hall has 2 trucks and 3 crews that need one.
The road crew takes truck #1.
The electricians take truck #2.
No truck is free, so the garbage crew waits.
The road crew is done and gives truck #1 back.
The garbage crew takes truck #1. It is the same truck, it was not made again.
```

## Conclusions

In this laboratory work I learned that creational patterns answer a simple question: who
makes an object, when, and how many of them. Before, the objects in my project were made
wherever they were needed. Now each of these decisions has its own place in the code.

The Singleton makes sure the whole program uses one set of settings. Without it, two parts
of the program could each have their own copy, and they could disagree about the default
deadline or the number of trucks. At first I used the singleton for the database, but the
reports change all the time and a real application can need more than one database, so
now the storage is made once in `main()` and given to the code that needs it.

The Builder made work orders easy to create. A work order has many parts and most of them
are optional, so instead of one long constructor where the values are easy to mix up, each
part is set by its name and the others get their default values from the settings.

The Factory Method lets every department choose its own kind of crew, while the steps for
handling a work order are written only once. A new department is just one new class, and
the old code stays the same.

As an extra, I tried the Object Pool with the city trucks. The trucks are made once and
passed from one crew to the next, instead of making a new truck for every job.

I did not use Prototype and Abstract Factory, because the project does not need them yet:
there are no objects that have to be copied and no families of related objects.

The classes from lab 1 worked with the new code without any changes. The report service
could use the storage that `main()` gives it right away, because in lab 1 it was written to
receive its storage from outside. That showed me the SOLID principles from the first lab were worth it.

## C++ used in the code

New things compared to lab 1:

| In the code | What it means |
| --- | --- |
| `static const AppConfig& getInstance()` | a static method: it belongs to the class, so it is called as `AppConfig::getInstance()`, without an object |
| `static AppConfig instance;` inside a function | made the first time the function runs, and it stays alive until the program ends |
| `const AppConfig&` | a reference: the object itself, not a copy of it. `const` means it can only be read, so nobody can change the settings |
| `AppConfig(const AppConfig&) = delete;` | `= delete` forbids this method. This one is the copy constructor, so copying an `AppConfig` does not compile |
| `AppConfig& operator=(const AppConfig&) = delete;` | forbids assigning one `AppConfig` to another with `=` |
| constructor under `private:` | only the code of the class itself can make an object |
| `&first == &second` | compares two addresses. The same address means the same object |
| `ReportStorage& storage` as a parameter | the function works on the storage it was given, not on a copy of it |
| `int reportId = 0;` | a field with a default value |
| `const string& priority` | the text is passed by reference, so it is not copied, and `const` means the method can't change it |
| `WorkOrder build() const` | a `const` method: it does not change the object it is called on |
| `return *this;` | `this` points to the current object, and `*this` is the object itself |
| `WorkOrderBuilder(...).setPriority(...).build()` | the methods are called one after another on the same builder |
| `virtual ~Crew() = default;` | the destructor is virtual, and `= default` lets the compiler write its body |
| `unique_ptr<Crew>` | a pointer that owns its object and deletes it by itself when the pointer goes out of scope |
| `make_unique<RoadCrew>()` | makes a `RoadCrew` on the heap and returns a `unique_ptr` to it |
| `override` together with `const` | the method in the subclass must match the base one exactly, `const` included |
| `explicit TruckPool(int size)` | the constructor can't be used for a hidden conversion, so `TruckPool pool = 2;` does not compile |
| `Truck(int number) : number(number) {}` | an initializer list: the field `number` is set from the parameter `number` before the body runs |
| `trucks.reserve(size)` | the vector makes room for every truck at once, instead of growing step by step |
| `trucks.emplace_back(i)` | builds the truck directly inside the vector, without making a copy first |
| `nullptr` | a pointer that points to nothing |
| `for (Truck& truck : trucks)` | the `&` means the loop works on the trucks in the vector, not on copies |
| `for (const Report& report : ...)` | the loop reads each report without copying it and can't change it |
| `size_t` | the type the standard library uses for sizes and positions, a number that can't be negative |
