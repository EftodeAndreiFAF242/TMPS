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
`ReportService`, `ConsoleNotifier`) and does not change them. Each pattern has its own
file:

| File | Pattern | Classes in it | What it decides about making objects |
| --- | --- | --- | --- |
| [Singleton.hpp](Singleton.hpp) | Singleton | `Database` | there is only one database |
| [Builder.hpp](Builder.hpp) | Builder | `WorkOrder`, `WorkOrderBuilder`, `WorkOrderPrinter` | a work order is made step by step |
| [FactoryMethod.hpp](FactoryMethod.hpp) | Factory Method | `Crew` and 3 crews, `Department` and 3 departments | each department chooses which crew it makes |
| [ObjectPool.hpp](ObjectPool.hpp) | Object Pool (extra) | `Truck`, `TruckPool` | trucks are made once and reused |

The demo is the function `runLab2()` in [main.cpp](../main.cpp).

## 1. Singleton

> A class has only one object, and the whole program reaches it from one place.

Every report has to be kept in one place. If two parts of the program each made their
own `ReportStorage`, a report saved by one part would be missing in the other. So the
storage lives inside `Database`, and the program can't make a second `Database`.

```cpp
class Database {
public:
    static Database& getInstance() {
        static Database instance;   // made at the first call, then the same object every time
        return instance;
    }

    Database(const Database& other) = delete;        // no copies
    void operator=(const Database& other) = delete;

    ReportStorage* getStorage() { return &storage; }

private:
    Database() { ... }   // private: only getInstance() can make a Database
    ReportStorage storage;
};
```

Three things together make sure there is only one database:

| In the code | What it stops |
| --- | --- |
| private constructor | `Database db;` written anywhere outside the class does not compile |
| `= delete` on the copy | `Database copy = Database::getInstance();` does not compile |
| `static Database instance;` | `getInstance()` makes the object only at the first call and returns it after that |

The database is made the first time someone asks for it, not when the program starts.
The C++ standard also guarantees that two threads calling `getInstance()` at the same
moment still get only one database.

The demo asks for the database twice, as `first` and `second`. The message
`The database was created.` appears once, and the two have the same address in memory.
The reports are saved through `first` and read through `second`. Running lab 2 a second
time from the menu shows the same thing: the database is not made again, and the reports
from the first run are still in it.

A singleton can be reached from anywhere, which hides who uses it. To keep the Dependency
Inversion from lab 1, only `main.cpp` calls `getInstance()`. `ReportService` still gets
its storage from outside, through its constructor:

```cpp
ReportService service(first.getStorage(), &validator, &notifier);
```

## 2. Builder

> Build a complex object step by step, giving only the parts that are needed.

A work order has six parts. Three are needed every time (the id of the report, its
category and the address) and three are optional (the priority, the deadline and a note):

```cpp
struct WorkOrder {
    int reportId = 0;
    string problem;
    string address;
    string priority = "Normal";
    int deadlineDays = 7;
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

Every value has a name next to it, and the parts that are not given keep their default
values. The calls can follow each other because every method returns the builder itself:

```cpp
WorkOrderBuilder& setPriority(string priority) {
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
    virtual Crew* createCrew() = 0;   // the factory method

    void handle(const WorkOrder& order) {
        Crew* crew = createCrew();    // the subclass decides which crew this is
        crew->work(order);
        delete crew;
    }
};

class RoadDepartment : public Department {
public:
    Crew* createCrew() override {
        return new RoadCrew();
    }
};
```

`handle()` knows only the `Crew` interface. The names `RoadCrew`, `ElectricianCrew` and
`GarbageCrew` appear only in the department that makes them. A new department, for
example one for parks, is one new subclass with its own `createCrew()`. `Department` and
the other departments are not edited, which is the Open/Closed Principle from lab 1.

The crew is made with `new` because it has to outlive `createCrew()`. So `handle()`
deletes it when the job is done. `Crew` has a virtual destructor, so `delete` destroys the
right kind of crew.

## 4. Object Pool (extra)

> Keep a few ready objects and lend them out, instead of making a new one every time.

The task does not require this pattern. City hall has a fixed number of trucks. A crew
borrows one for a job, gives it back when the job is done, and the next crew gets that
same truck.

```cpp
class TruckPool {
public:
    TruckPool(int size);          // makes every truck, once
    Truck* acquire();             // lends a free truck, or nullptr if all are in use
    void release(Truck* truck);   // takes a truck back
private:
    vector<Truck> trucks;
};
```

In the demo, the pool has 2 trucks and 3 crews need one. The third crew gets `nullptr`
and waits. When the road crew gives truck #1 back, the garbage crew gets truck #1, the
same object, which was not made again.

In real programs the pool holds objects that are slow to make or that there are only a
few of, like connections to a database.

## Results

```
=== Laboratory work 2: Creational design patterns ===

--- 1. Singleton ---
[database] The database was created.
Both calls returned the same database.
[console] Report #1 was registered.
[console] Report #2 was registered.
[console] Report #3 was registered.
The reports were saved through "first" and are read through "second":
#1 [Pothole] Deep pothole in front of the school
#2 [Street light] The street light on the corner is broken
#3 [Garbage] Garbage bags left near the park entrance

--- 2. Builder ---
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

Each pattern moves the decision about making an object to one place:

- Singleton put the decision "how many databases" inside `Database`, so the program can't
  end up with two storages.
- Builder made a work order with many optional parts easy to read and hard to get wrong.
- Factory Method let each department choose its crew, while the steps of handling a work
  order are written once.
- Object Pool (extra) reused a few trucks instead of making a new one for every job.

The lab 1 classes were used without any change. `ReportService` works with the
singleton's storage because it was written to receive its storage from outside.

## C++ used in the code

New things compared to lab 1:

| In the code | What it means |
| --- | --- |
| `static Database& getInstance()` | a static method: it belongs to the class, so it is called as `Database::getInstance()`, without an object |
| `static Database instance;` inside a function | made the first time the function runs, and it stays alive until the program ends |
| `Database&` | a reference: the object itself, not a copy of it |
| `Database(const Database& other) = delete;` | `= delete` forbids this method. This one is the copy constructor, so copying a `Database` does not compile |
| `void operator=(...) = delete;` | forbids assigning one `Database` to another with `=` |
| constructor under `private:` | only the code of the class itself can make an object |
| `&first == &second` | compares two addresses. The same address means the same object |
| `string priority = "Normal";` | a field with a default value |
| `return *this;` | `this` points to the current object, and `*this` is the object itself |
| `WorkOrderBuilder(...).setPriority(...).build()` | the methods are called one after another on the same builder |
| `new RoadCrew()` | makes an object that stays alive until `delete` is called, and returns a pointer to it |
| `delete crew;` | destroys an object made with `new` |
| `nullptr` | a pointer that points to nothing |
| `for (Truck& truck : trucks)` | the `&` means the loop works on the trucks in the vector, not on copies |
