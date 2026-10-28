// Glossary: the words used in the quiz and the slides, explained for beginners.
// Each word has a short explanation and an example:
//   code - a small C++ example (or a small text drawing)
//   svg  - a small UML drawing (only in the "Reading the UML diagrams" group)

const GLOSSARY = [
  {
    title: "Object-oriented basics",
    words: [
      {
        word: "OOP (object-oriented programming)",
        text: "A way of writing programs where the code is organized into classes and objects. Each object keeps its data together with the functions that work on that data. SOLID and design patterns are rules and ideas for writing good OOP code.",
        code:
`class Circle {                  // the plan
public:
    int radius;                                        // data
    double area() { return 3.14 * radius * radius; }   // behavior
};

Circle c;          // an object made from the plan
c.radius = 2;
c.area();          // 12.56`,
      },
      {
        word: "Class",
        text: "A blueprint (a plan) that describes what data an object will have and what it can do. The class itself holds no data. It only describes what its objects look like.",
        code:
`class Circle {
    int radius;          // data
public:
    double area();       // what it can do
};`,
      },
      {
        word: "Object",
        text: "A real thing made from a class, living in memory with its own data. From one class you can make many objects.",
        code:
`Circle a(1);   // object a, radius 1
Circle b(5);   // object b, radius 5
// same class, two different objects, each with its own radius`,
      },
      {
        word: "Instance",
        text: "Another word for object. \"An instance of Circle\" means \"an object made from the Circle class\". A Singleton is a class that allows only one instance.",
        code:
`Circle a(1);    // a is an instance of Circle
Circle b(5);    // b is another instance of Circle

Database& x = Database::getInstance();
Database& y = Database::getInstance();
// Singleton: x and y are the SAME instance`,
      },
      {
        word: "Instantiation (class instantiation)",
        text: "Creating an object from a class. Creational design patterns are \"all about class instantiation\", meaning they are about how objects get created.",
        code:
`Circle c(3);                // instantiation
Circle* p = new Circle(3);  // instantiation with new`,
      },
      {
        word: "Attribute (field, data member)",
        text: "A variable that belongs to an object. In the Singleton UML diagram, uniqueInstance and singletonData are attributes.",
        code:
`class Report {
    std::string text;      // attribute
    int priority;          // attribute
};`,
      },
      {
        word: "Method (member function)",
        text: "A function that belongs to a class and works with the object's data. In UML diagrams methods are written with (), like Clone().",
        code:
`class Report {
    std::string text;
public:
    void setText(std::string t) { text = t; }   // method
    std::string getText() { return text; }      // method
};

Report r;
r.setText("Broken street light");   // calling a method`,
      },
      {
        word: "Constructor",
        text: "A special method with the same name as the class. It runs automatically when an object is created and prepares the object's data.",
        code:
`class Circle {
    int radius;
public:
    Circle(int r) : radius(r) {}   // constructor
};

Circle c(4);   // the constructor runs here, radius = 4`,
      },
      {
        word: "Destructor",
        text: "A special method named like the class with a ~ in front (~Shape). It runs automatically when an object is destroyed. A virtual destructor in a base class makes sure the right destructor runs when you delete a subclass object through a base class pointer.",
        code:
`class Shape {
public:
    virtual ~Shape() = default;     // virtual destructor
};
class Circle : public Shape {
public:
    ~Circle() { std::cout << "Circle destroyed"; }
};

Shape* s = new Circle();
delete s;    // runs ~Circle(), then ~Shape()`,
      },
      {
        word: "public, private, protected",
        text: "They say who can use a member of a class. public: everyone. private: only the class itself. protected: the class and its subclasses. A Singleton's constructor is private, so code outside the class cannot create objects.",
        code:
`class Account {
public:
    void deposit(int x) { balance += x; }   // anyone can call it
private:
    int balance = 0;                        // only Account can use it
};

Account a;
a.deposit(10);    // OK
a.balance = 99;   // ERROR: balance is private`,
      },
      {
        word: "Encapsulation (encapsulated)",
        text: "Hiding an object's data inside the class (making it private), so other code can use it only through the class's methods. The Singleton's instance is \"static encapsulated\": it is hidden inside the class and you reach it only through getInstance().",
        code:
`class Account {
    int balance = 0;                 // hidden data
public:
    void deposit(int x) {
        if (x > 0) balance += x;     // the class controls every change
    }
    int getBalance() { return balance; }
};`,
      },
      {
        word: "static",
        text: "A static member belongs to the class itself, not to one object. There is only one copy of it, shared by everyone. A static method can be called without any object, using the class name.",
        code:
`class Counter {
public:
    static int count;            // one copy for the whole class
    Counter() { count++; }
};
int Counter::count = 0;

Counter a, b, c;
std::cout << Counter::count;     // 3`,
      },
      {
        word: "Inheritance",
        text: "When a class is built on top of another class and gets its data and methods. It describes an \"is a\" relation: a Circle is a Shape.",
        code:
`class Shape {
public:
    std::string color;
};
class Circle : public Shape {    // Circle inherits from Shape
public:
    int radius;
};

Circle c;
c.color = "red";    // color comes from Shape
c.radius = 2;`,
      },
      {
        word: "Base class (parent class, superclass)",
        text: "The class that other classes inherit from. Shape is the base class of Circle and Square.",
        code:
`       Shape        <- base class
      /     \\
 Circle    Square   <- derived classes`,
      },
      {
        word: "Derived class (subclass, child class)",
        text: "A class that inherits from another class. \"Several related derived classes\" (Factory Method slide) means several subclasses of the same base class.",
        code:
`class Shape  { /* ... */ };
class Circle : public Shape { /* ... */ };   // derived class
class Square : public Shape { /* ... */ };   // derived class
// Circle and Square are "related derived classes"`,
      },
      {
        word: "virtual",
        text: "A keyword that lets a subclass replace a method of the base class. When you call the method through a base class pointer or reference, the subclass's version runs.",
        code:
`class Shape {
public:
    virtual std::string name() { return "shape"; }
};
class Circle : public Shape {
public:
    std::string name() override { return "circle"; }
};

Shape* s = new Circle();
s->name();   // "circle"  (without virtual it would be "shape")`,
      },
      {
        word: "override",
        text: "Written after a method in a subclass. It means \"this replaces the virtual method from the base class\". The compiler checks that such a method really exists in the base class.",
        code:
`class Circle : public Shape {
public:
    std::string name() override { return "circle"; }  // OK
    std::string nmae() override { return "oops"; }    // ERROR: typo,
};                                                    // Shape has no nmae()`,
      },
      {
        word: "Pure virtual method (= 0)",
        text: "A virtual method with no code in the base class, written with = 0 at the end. Every concrete subclass must write the code for it.",
        code:
`class Shape {
public:
    virtual double area() = 0;     // pure virtual: no code here
};
class Square : public Shape {
    double a = 2;
public:
    double area() override { return a * a; }   // must be written
};`,
      },
      {
        word: "Abstract class",
        text: "A class with at least one pure virtual method. You cannot create objects of it directly; it only says what its subclasses must do. In UML diagrams abstract names are written in italics (Product, Creator, Builder).",
        code:
`class Shape {                  // abstract: has a pure virtual method
public:
    virtual double area() = 0;
};

Shape s;          // ERROR: cannot create an abstract class
Square q;         // OK: Square is concrete
Shape* p = &q;    // OK: a pointer of the abstract type`,
      },
      {
        word: "Interface",
        text: "A list of methods that a class promises to have, without their code. C++ has no interface keyword, so we use an abstract class with only pure virtual methods, like Notifier or Worker.",
        code:
`class Notifier {                         // an interface
public:
    virtual void send(std::string msg) = 0;
    virtual ~Notifier() = default;
};`,
      },
      {
        word: "Implement",
        text: "To write the real code of a method that was only declared. \"Implementing an interface\" means inheriting from it and writing the code for all its methods.",
        code:
`class EmailNotifier : public Notifier {    // implements Notifier
public:
    void send(std::string msg) override {
        std::cout << "Email: " << msg;     // the real code
    }
};`,
      },
      {
        word: "Concrete class",
        text: "A normal class where every method has code, so you can create objects of it. The opposite of abstract. In the diagrams: ConcreteProduct, ConcreteCreator, ConcreteBuilder. \"Depending on concrete things\" means using one specific class directly.",
        code:
`class Square : public Shape {    // concrete: every method has code
public:
    double area() override { return 4; }
};

Square s;    // OK, you can create it`,
      },
      {
        word: "Abstraction",
        text: "Looking at what something does, not at how it does it. In code, an abstraction is usually an interface or an abstract class (Notifier), and the details are in concrete classes (EmailNotifier, SmsNotifier).",
        code:
`void notifyCitizen(Notifier& n) {     // knows only WHAT: send()
    n.send("Your report was fixed");
}

EmailNotifier email;
SmsNotifier sms;
notifyCitizen(email);   // HOW it is sent is hidden
notifyCitizen(sms);     // inside the concrete classes`,
      },
      {
        word: "Polymorphism",
        text: "\"Many forms\": the same call does different things depending on the real object. It works through virtual methods.",
        code:
`std::vector<Shape*> shapes = { new Circle(1), new Square(2) };

for (Shape* s : shapes)
    std::cout << s->area() << "\\n";   // same call, different code runs`,
      },
      {
        word: "Composition",
        text: "Building a class from other objects that it keeps as members (a \"has a\" relation). It is the main alternative to inheritance.",
        code:
`class Engine {
public:
    void start();
};
class Car {
    Engine engine;                    // a Car HAS an Engine
public:
    void drive() { engine.start(); }
};`,
      },
      {
        word: "Delegation",
        text: "When an object gives a job to another object instead of doing it itself. Object-creation patterns use delegation: another object (a factory, a builder, a prototype) does the creating.",
        code:
`class Dispatcher {
    Notifier& notifier;
public:
    Dispatcher(Notifier& n) : notifier(n) {}
    void alert(std::string msg) {
        notifier.send(msg);    // Dispatcher does not send it itself,
    }                          // it delegates the job to notifier
};`,
      },
      {
        word: "Client",
        text: "The code that uses a class or an interface. In the diagrams, Client is the code that asks for new objects, for example by calling prototype->Clone() or by using an AbstractFactory.",
        code:
`// main() is a client of Database: it uses it
int main() {
    Database& db = Database::getInstance();
    db.getStorage();
}`,
      },
      {
        word: "Dependency (depends on)",
        text: "Class A depends on class B when A uses B: it keeps a B, calls B's methods, or creates a B. If B changes, A may have to change too.",
        code:
`class ReportService {
    MySqlDatabase db;          // ReportService depends on MySqlDatabase
public:
    void submit(std::string r) { db.save(r); }
};
// if MySqlDatabase::save() changes, ReportService may break`,
      },
      {
        word: "Module",
        text: "A part of a program that groups related code, for example a file, a group of classes or a library. Your own project is split into modules:",
        code:
`TMPS/
  Lab1/      <- SOLID examples
  Lab2/      <- creational patterns
  main.cpp   <- uses both modules`,
      },
      {
        word: "High-level and low-level modules",
        text: "High-level modules hold the main logic of the program (what to do with a report). Low-level modules handle the details (how to save the data). The Dependency Inversion Principle says both should depend on an abstraction between them.",
        code:
`ReportService    <- high level:
      |             WHAT to do
      v
MySqlDatabase    <- low level:
                    HOW to save it`,
      },
    ],
  },
  {
    title: "C++ words from the code",
    words: [
      {
        word: "Pointer (*), new, delete, nullptr",
        text: "A pointer holds the address of an object in memory. new creates an object and gives back its address. delete destroys that object. nullptr means the pointer points to nothing yet.",
        code:
`Logger* p = nullptr;   // points to nothing
p = new Logger();      // now points to a new Logger
p->log("hello");       // use the object through the pointer: ->
delete p;              // destroy it`,
      },
      {
        word: "Reference (&)",
        text: "Another name for an object that already exists, written Type&. The function works with the original object, not a copy. A base class reference can refer to an object of any subclass.",
        code:
`void grow(Circle& c) { c.radius = 10; }   // works on the original

Circle a(1);
grow(a);          // a.radius is now 10

Shape& s = a;     // a Shape reference to a Circle: allowed`,
      },
      {
        word: "this, *this and copying",
        text: "this is a pointer to the current object, so *this is the object itself. new Circle(*this) creates a new Circle that is a copy of the current one. That is how clone() makes a copy.",
        code:
`class Circle : public Shape {
    int radius;
public:
    Shape* clone() const override {
        return new Circle(*this);   // *this = this circle; make a copy
    }
};`,
      },
      {
        word: "Exception (throw)",
        text: "throw stops the normal work of the program and reports an error. If no code catches it, the program crashes. That is what happens with Penguin::fly() in the Liskov example.",
        code:
`try {
    Penguin p;
    p.fly();                     // throws std::logic_error
} catch (std::logic_error& e) {
    std::cout << e.what();       // prints: can't fly
}`,
      },
    ],
  },
  {
    title: "SOLID principles",
    words: [
      {
        word: "Design principle",
        text: "A general rule for good design. It does not give you ready code; it tells you what good code should look like. SOLID is a set of 5 such principles.",
        code:
`Rule: "A class should do one job."

Code that follows the rule:
  class Report    -> keeps the data
  class FileSaver -> saves files
  class Mailer    -> sends emails`,
      },
      {
        word: "SOLID",
        text: "An acronym (a word made from first letters) for 5 OOP design principles.",
        code:
`S  Single Responsibility
   one job per class
O  Open Closed
   add new code, don't edit old code
L  Liskov Substitution
   a subclass can replace its parent
I  Interface Segregation
   small interfaces, not one big one
D  Dependency Inversion
   depend on interfaces`,
      },
      {
        word: "Maintainable, testable, extendable",
        text: "The goals of SOLID. Maintainable code is easy to fix and change later. Testable code is easy to check with tests. Extendable code is easy to add new features to.",
        code:
`// Extendable: a new kind of notifier = just a new class
class PushNotifier : public Notifier { /* ... */ };

// Testable: give Dispatcher a fake notifier in a test
class FakeNotifier : public Notifier {
    void send(std::string) override { /* only count the calls */ }
};`,
      },
      {
        word: "Responsibility (reason to change)",
        text: "A responsibility is one job a piece of code does. Every job is a possible reason to change that code, so one job means one reason to change.",
        code:
`class Report {
    void addProblem();  // job 1: keep data
    void saveToFile();  // job 2: save it
    void sendEmail();   // job 3: notify
};
// 3 jobs = 3 reasons to change`,
      },
      {
        word: "Single Responsibility Principle (SRP)",
        text: "Every module, class or function should do one job only, so it has only one reason to change. The Report class above, split correctly:",
        code:
`class Report      { public: void addProblem(std::string t); };
class ReportSaver { public: void save(const Report& r); };
class Mailer      { public: void send(std::string to); };
// each class: one job, one reason to change`,
      },
      {
        word: "Extension and modification",
        text: "Extension means adding new behavior by adding new code, for example a new subclass. Modification means editing code that already works. The Open Closed Principle says: allow extension, avoid modification.",
        code:
`// Modification: editing a function that already works
double area(Shape& s) {
    if (s.type == "circle")   return /* ... */;
    if (s.type == "triangle") return /* ... */;   // <- edited
}

// Extension: adding a new class, old code stays the same
class Triangle : public Shape {
    double area() override { /* ... */ }
};`,
      },
      {
        word: "Open Closed Principle (OCP)",
        text: "Code should be open for extension and closed for modification: you add new features without editing the classes that already work.",
        code:
`double total(std::vector<Shape*>& shapes) {   // never needs editing
    double sum = 0;
    for (Shape* s : shapes) sum += s->area();
    return sum;
}
// a new Triangle class works here without changing total()`,
      },
      {
        word: "Substitutable",
        text: "Can be put in the place of something else and still work. A subclass object is substitutable for its base class if the code using the base class keeps working with it.",
        code:
`void printArea(Shape& s) { std::cout << s.area(); }

Circle c(1);
Square q(2);
printArea(c);   // works
printArea(q);   // works: both can stand in for a Shape`,
      },
      {
        word: "Liskov Substitution Principle (LSP)",
        text: "Objects of a class should be replaceable by objects of its subclasses without breaking the program. It is named after Barbara Liskov. The Penguin problem, fixed: only birds that can fly get fly().",
        code:
`class Bird       { public: virtual void eat(); };
class FlyingBird : public Bird { public: virtual void fly(); };

class Sparrow : public FlyingBird { /* can eat and fly */ };
class Penguin : public Bird       { /* can eat, no fly() to break */ };`,
      },
      {
        word: "Interface Segregation Principle (ISP)",
        text: "Segregation means separation. A class should not be forced to implement methods it does not use, so big interfaces should be split into smaller ones. The Worker problem, fixed:",
        code:
`class Workable { public: virtual void work() = 0; };
class Eatable  { public: virtual void eat()  = 0; };

class Human : public Workable, public Eatable { /* work + eat */ };
class Robot : public Workable { /* only work, no empty eat() */ };`,
      },
      {
        word: "Dependency Inversion Principle (DIP)",
        text: "Inversion means turning around. Classes should depend on abstractions (interfaces), not on concrete classes. Instead of a high-level class using a low-level class directly, both depend on an interface between them.",
        code:
`Before:
  ReportService ---> MySqlDatabase

After:
  ReportService ---> Storage
                       ^   (interface)
                       |
  MySqlDatabase -------+

class Storage {
public:
    virtual void save(std::string d) = 0;
};
class MySqlDatabase : public Storage {};
class ReportService {
    Storage& storage;   // only the interface
public:
    ReportService(Storage& s) : storage(s) {}
};`,
      },
    ],
  },
  {
    title: "Creational design patterns",
    words: [
      {
        word: "Design pattern",
        text: "A known, reusable solution to a problem that appears often in software design. It is a plan for how to organize classes, not ready code you copy.",
        code:
`Problem:  "The program needs exactly
           one Database."
Pattern:  Singleton
Solution: private constructor
          + static instance
          + getInstance()`,
      },
      {
        word: "Gang of Four (GoF)",
        text: "The four authors of the 1994 book \"Design Patterns: Elements of Reusable Object-Oriented Software\". The slides' diagrams come from their book.",
        code:
`Authors: Erich Gamma, Richard Helm,
         Ralph Johnson, John Vlissides
Book:    Design Patterns (1994)
         23 patterns, 5 are creational:
         Singleton, Prototype,
         Factory Method,
         Abstract Factory, Builder`,
      },
      {
        word: "Creational design patterns",
        text: "Patterns about how objects are created.",
        code:
`Singleton
  only one object of a class
Prototype
  copy an existing object
Factory Method
  a subclass decides what to create
Abstract Factory
  create a family of matching objects
Builder
  build a complex object step by step`,
      },
      {
        word: "Class-creation and object-creation patterns",
        text: "Class-creation patterns use inheritance: a subclass decides which object is created (Factory Method). Object-creation patterns use delegation: another object does the creating (Abstract Factory, Builder, Prototype, Singleton).",
        code:
`// Class-creation (inheritance): a SUBCLASS decides
class RoadLogistics : public Logistics {
    Transport* createTransport() override { return new Truck(); }
};

// Object-creation (delegation): ANOTHER OBJECT creates it
Button* b = factory.createButton();`,
      },
      {
        word: "Singleton",
        text: "A class that allows only one instance and gives everyone access to it through a static method. Its constructor is private and the instance is stored in a static member.",
        code:
`class Logger {
    static Logger* instance;      // static encapsulated instance
    Logger() {}                   // private constructor
public:
    static Logger* getInstance() {
        if (instance == nullptr) instance = new Logger();
        return instance;
    }
};

Logger* a = Logger::getInstance();
Logger* b = Logger::getInstance();   // a == b, the same object`,
      },
      {
        word: "Thread (thread safe)",
        text: "A thread is one line of execution; a program can run several threads at the same time. Thread safe code works correctly even when several threads use it at once. Since C++11, a static local variable is created only once even with many threads, which is how your Lab 2 Database does it:",
        code:
`Database& Database::getInstance() {
    static Database instance;   // created once, thread safe (C++11)
    return instance;
}`,
      },
      {
        word: "Prototype",
        text: "A pattern where new objects are made by copying (cloning) an existing object that is already set up, instead of building them from zero.",
        code:
`Circle original(5);
Shape* copy = original.clone();   // a new Circle, also radius 5
// copy is a different object with the same data`,
      },
      {
        word: "Clone",
        text: "To make a copy of an object. clone() returns a new object with the same data as the original.",
        code:
`class Circle : public Shape {
    int radius;
public:
    Shape* clone() const override {
        return new Circle(*this);   // new object, same data
    }
};`,
      },
      {
        word: "Cache",
        text: "A place where things are kept ready so they can be reused quickly. In Prototype, a collection keeps the prototype objects ready to be cloned.",
        code:
`std::map<std::string, Shape*> prototypes;   // the cache
prototypes["small"] = new Circle(1);
prototypes["big"]   = new Circle(100);

Shape* s = prototypes["big"]->clone();      // copy, don't rebuild`,
      },
      {
        word: "Factory",
        text: "A class or method whose job is to create objects, so the rest of the code does not have to call new on concrete classes itself.",
        code:
`Shape* makeShape(std::string type) {     // a simple factory
    if (type == "circle") return new Circle(1);
    if (type == "square") return new Square(1);
    return nullptr;
}

Shape* s = makeShape("circle");   // the caller never writes new Circle`,
      },
      {
        word: "Factory Method",
        text: "A method in a base class that creates an object. Subclasses override it to decide which concrete class gets created.",
        code:
`class Logistics {
public:
    virtual Transport* createTransport() = 0;    // the factory method
};
class SeaLogistics : public Logistics {
    Transport* createTransport() override { return new Ship(); }
};`,
      },
      {
        word: "Product and ConcreteProduct",
        text: "In design patterns, the product is the object being created. Product is the abstract type, ConcreteProduct is the real class that gets created.",
        code:
`class Transport { public: virtual void deliver() = 0; };   // Product
class Truck : public Transport { /* ... */ };   // ConcreteProduct
class Ship  : public Transport { /* ... */ };   // ConcreteProduct`,
      },
      {
        word: "Creator and ConcreteCreator",
        text: "In Factory Method: Creator is the base class that declares FactoryMethod() and uses it. ConcreteCreator is the subclass that overrides it and returns a ConcreteProduct.",
        code:
`class Logistics {                             // Creator
public:
    virtual Transport* createTransport() = 0;
    void planDelivery() {
        Transport* t = createTransport();     // uses the factory method
        t->deliver();
        delete t;
    }
};
class RoadLogistics : public Logistics {      // ConcreteCreator
    Transport* createTransport() override { return new Truck(); }
};`,
      },
      {
        word: "Abstract Factory",
        text: "An interface with one create method for each product type, used to create a whole family of objects that belong together, without naming their concrete classes.",
        code:
`void buildScreen(GUIFactory& f) {
    Button*   b = f.createButton();
    Checkbox* c = f.createCheckbox();   // always the same style as b
}

DarkFactory dark;
buildScreen(dark);    // dark button + dark checkbox`,
      },
      {
        word: "Family of related objects",
        text: "Objects made to work together. An Abstract Factory makes sure all the objects you get are from the same family.",
        code:
`DarkFactory makes family 1:
   DarkButton + DarkCheckbox

LightFactory makes family 2:
   LightButton + LightCheckbox`,
      },
      {
        word: "Builder",
        text: "A pattern that builds a complex object step by step. The same steps can produce different results (different representations).",
        code:
`Cook cook;
MargheritaBuilder m;
PepperoniBuilder  p;

Pizza a = cook.make(m);   // the same steps...
Pizza b = cook.make(p);   // ...give a different pizza`,
      },
      {
        word: "Director",
        text: "In Builder: the class that knows the order of the steps and calls them on a builder.",
        code:
`class Cook {                          // Director
public:
    Pizza make(PizzaBuilder& b) {     // knows the ORDER of the steps
        b.buildDough();
        b.buildSauce();
        b.buildTopping();
        return b.getResult();
    }
};`,
      },
      {
        word: "ConcreteBuilder",
        text: "In Builder: a subclass of Builder that does each step its own way and gives back the finished product with GetResult().",
        code:
`class MargheritaBuilder : public PizzaBuilder {
    Pizza pizza;
public:
    void buildDough()   override { pizza.dough = "thin"; }
    void buildSauce()   override { pizza.sauce = "tomato"; }
    void buildTopping() override { pizza.topping = "mozzarella"; }
    Pizza getResult()   override { return pizza; }
};`,
      },
      {
        word: "Representation",
        text: "The final form of the built object. In Builder, the same construction process (the same steps) can give different representations.",
        code:
`Same steps:
  buildTitle("Pothole")
  buildBody("Main street")

HtmlReportBuilder gives:
  <h1>Pothole</h1><p>Main street</p>
TextReportBuilder gives:
  POTHOLE
  Main street`,
      },
    ],
  },
  {
    title: "Reading the UML diagrams",
    words: [
      {
        word: "UML (class diagram)",
        text: "UML (Unified Modeling Language) is a standard way to draw software designs. The slides use class diagrams, which show classes and how they are connected. This one shows an abstract Shape with two subclasses:",
        svg:
`<svg class="uml" viewBox="0 0 320 166">
  <rect x="110" y="10" width="100" height="50"/>
  <text x="160" y="29" text-anchor="middle" font-weight="bold" font-style="italic">Shape</text>
  <line x1="110" y1="37" x2="210" y2="37"/>
  <text x="120" y="53" font-style="italic">area()</text>
  <path d="M160 60 L152 74 L168 74 Z"/>
  <path class="line" d="M160 74 V90 M60 90 H260 M60 90 V106 M260 90 V106"/>
  <rect x="10" y="106" width="100" height="50"/>
  <text x="60" y="125" text-anchor="middle" font-weight="bold">Circle</text>
  <line x1="10" y1="133" x2="110" y2="133"/>
  <text x="20" y="149">area()</text>
  <rect x="210" y="106" width="100" height="50"/>
  <text x="260" y="125" text-anchor="middle" font-weight="bold">Square</text>
  <line x1="210" y1="133" x2="310" y2="133"/>
  <text x="220" y="149">area()</text>
</svg>`,
        code:
`class Shape  { public: virtual double area() = 0; };
class Circle : public Shape { public: double area() override; };
class Square : public Shape { public: double area() override; };`,
      },
      {
        word: "Class box",
        text: "Each class is drawn as a box: the name on top, then its methods, then its data. A name written in italics means an abstract class or a pure virtual method.",
        svg:
`<svg class="uml" viewBox="0 0 340 146">
  <rect x="10" y="10" width="200" height="126"/>
  <text x="110" y="30" text-anchor="middle" font-weight="bold">Singleton</text>
  <line x1="10" y1="40" x2="210" y2="40"/>
  <text x="20" y="58">static Instance()</text>
  <text x="20" y="76">GetSingletonData()</text>
  <line x1="10" y1="86" x2="210" y2="86"/>
  <text x="20" y="104">static uniqueInstance</text>
  <text x="20" y="122">singletonData</text>
  <text class="label" x="222" y="30">&#8592; class name</text>
  <text class="label" x="222" y="67">&#8592; methods</text>
  <text class="label" x="222" y="113">&#8592; data</text>
</svg>`,
        code:
`class Singleton {
public:
    static Singleton* Instance();
    Data GetSingletonData();
private:
    static Singleton* uniqueInstance;
    Data singletonData;
};`,
      },
      {
        word: "Triangle arrow (inheritance)",
        text: "A line ending with a hollow triangle goes from a subclass up to its base class.",
        svg:
`<svg class="uml" viewBox="0 0 320 130">
  <rect x="80" y="10" width="140" height="36"/>
  <text x="150" y="33" text-anchor="middle" font-weight="bold" font-style="italic">Creator</text>
  <path d="M150 46 L142 60 L158 60 Z"/>
  <line x1="150" y1="60" x2="150" y2="84"/>
  <rect x="80" y="84" width="140" height="36"/>
  <text x="150" y="107" text-anchor="middle" font-weight="bold">ConcreteCreator</text>
  <text class="label" x="230" y="33">base class</text>
  <text class="label" x="230" y="107">subclass</text>
</svg>`,
        code: `class ConcreteCreator : public Creator { /* ... */ };`,
      },
      {
        word: "Dashed arrow (creates)",
        text: "A dashed line with an arrow means one class creates objects of the other.",
        svg:
`<svg class="uml" viewBox="0 0 360 60">
  <rect x="5" y="12" width="140" height="36"/>
  <text x="75" y="35" text-anchor="middle" font-weight="bold">ConcreteCreator</text>
  <line class="dash" x1="145" y1="30" x2="203" y2="30"/>
  <path class="fill" d="M215 30 L203 24 L203 36 Z"/>
  <rect x="215" y="12" width="140" height="36"/>
  <text x="285" y="35" text-anchor="middle" font-weight="bold">ConcreteProduct</text>
</svg>`,
        code:
`class ConcreteCreator : public Creator {
    Product* FactoryMethod() override {
        return new ConcreteProduct();     // creates a ConcreteProduct
    }
};`,
      },
      {
        word: "Solid arrow (has a reference)",
        text: "A solid line with an arrow means one class keeps and uses an object of the other. The word on the line is the name of that member.",
        svg:
`<svg class="uml" viewBox="0 0 360 70">
  <rect x="5" y="22" width="110" height="36"/>
  <text x="60" y="45" text-anchor="middle" font-weight="bold">Client</text>
  <line x1="115" y1="40" x2="233" y2="40"/>
  <path class="fill" d="M245 40 L233 34 L233 46 Z"/>
  <text x="175" y="32" text-anchor="middle">prototype</text>
  <rect x="245" y="22" width="110" height="36"/>
  <text x="300" y="45" text-anchor="middle" font-weight="bold" font-style="italic">Prototype</text>
</svg>`,
        code:
`class Client {
    Prototype* prototype;      // the Client keeps a Prototype
public:
    void Operation() { Prototype* p = prototype->Clone(); }
};`,
      },
      {
        word: "Diamond (part of)",
        text: "A line that starts with a hollow diamond means one object holds the other as a part.",
        svg:
`<svg class="uml" viewBox="0 0 360 70">
  <rect x="5" y="22" width="110" height="36"/>
  <text x="60" y="45" text-anchor="middle" font-weight="bold">Director</text>
  <path d="M115 40 L127 34 L139 40 L127 46 Z"/>
  <line x1="139" y1="40" x2="233" y2="40"/>
  <path class="fill" d="M245 40 L233 34 L233 46 Z"/>
  <text x="187" y="32" text-anchor="middle">builder</text>
  <rect x="245" y="22" width="110" height="36"/>
  <text x="300" y="45" text-anchor="middle" font-weight="bold" font-style="italic">Builder</text>
</svg>`,
        code:
`class Director {
    Builder* builder;          // the Director holds a Builder
public:
    void Construct() { builder->BuildPart(); }
};`,
      },
      {
        word: "Note",
        text: "A box with a folded corner, linked by a dashed line to a method. It shows what the method does.",
        svg:
`<svg class="uml" viewBox="0 0 360 84">
  <rect x="5" y="10" width="150" height="64"/>
  <text x="80" y="30" text-anchor="middle" font-weight="bold">Singleton</text>
  <line x1="5" y1="38" x2="155" y2="38"/>
  <text x="15" y="60">static Instance()</text>
  <circle cx="137" cy="55" r="3"/>
  <line class="dash" x1="140" y1="55" x2="190" y2="55"/>
  <path d="M190 35 L343 35 L355 47 L355 75 L190 75 Z"/>
  <path class="line" d="M343 35 V47 H355"/>
  <text x="198" y="60">return uniqueInstance</text>
</svg>`,
        code:
`static Singleton* Instance() {
    return uniqueInstance;      // what the note says
}`,
      },
    ],
  },
];
