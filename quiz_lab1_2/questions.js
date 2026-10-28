// Quiz questions, taken from the course slides
// ("SOLID Principles" and "Creational Design Patterns", Software Design Techniques and Mechanisms).
//
// Each question has:
//   topic   - "SOLID principles" or "Creational patterns"
//   text    - the question
//   code    - optional C++ code shown under the question
//   options - 4 answers; the FIRST one is the correct one (the page shuffles them)
//   why     - short explanation shown after answering

const QUESTIONS = [
  // ---------------- SOLID principles: theory ----------------
  {
    topic: "SOLID principles",
    text: "What is SOLID?",
    options: [
      "An acronym for 5 OOP design principles",
      "A group of 5 creational design patterns",
      "A C++ library for writing tests",
      "A set of 5 rules for naming classes",
    ],
    why: "Overview slide: SOLID is an acronym for 5 OOP design principles.",
  },
  {
    topic: "SOLID principles",
    text: "According to the slides, which of these is NOT a goal of SOLID?",
    options: [
      "Making the program run faster",
      "Making software more understandable",
      "Making software easier to maintain and test",
      "Making software extendable",
    ],
    why: "Overview slide: the intent is to make software more understandable, easier to maintain/test and extendable. Speed is not mentioned.",
  },
  {
    topic: "SOLID principles",
    text: "What does the letter S in SOLID stand for?",
    options: [
      "Single Responsibility Principle",
      "Singleton Principle",
      "Separation of State Principle",
      "Simple Structure Principle",
    ],
    why: "S = Single Responsibility Principle.",
  },
  {
    topic: "SOLID principles",
    text: "What does the letter O in SOLID stand for?",
    options: [
      "Open Closed Principle",
      "Object Creation Principle",
      "Override Principle",
      "Open Access Principle",
    ],
    why: "O = Open Closed Principle.",
  },
  {
    topic: "SOLID principles",
    text: "What does the letter L in SOLID stand for?",
    options: [
      "Liskov Substitution Principle",
      "Layered Structure Principle",
      "Loose Coupling Principle",
      "Lazy Loading Principle",
    ],
    why: "L = Liskov Substitution Principle.",
  },
  {
    topic: "SOLID principles",
    text: "What does the letter I in SOLID stand for?",
    options: [
      "Interface Segregation Principle",
      "Inheritance Separation Principle",
      "Instance Isolation Principle",
      "Interface Implementation Principle",
    ],
    why: "I = Interface Segregation Principle.",
  },
  {
    topic: "SOLID principles",
    text: "What does the letter D in SOLID stand for?",
    options: [
      "Dependency Inversion Principle",
      "Dependency Injection Principle",
      "Data Integrity Principle",
      "Derived Implementation Principle",
    ],
    why: "D = Dependency Inversion Principle.",
  },
  {
    topic: "SOLID principles",
    text: "The Single Responsibility Principle applies to which pieces of software?",
    options: [
      "Modules, classes and functions",
      "Only classes",
      "Only modules",
      "Only interfaces",
    ],
    why: "SRP slide: every piece of software (i.e. module, class or function) should be responsible over a single part of the functionality.",
  },
  {
    topic: "SOLID principles",
    text: "Following the Single Responsibility Principle, how many reasons to change should a class have?",
    options: [
      "Only one",
      "At most two",
      "One for each of its methods",
      "As many as needed, if they are documented",
    ],
    why: "SRP slide: being responsible only for one thing, it will have only one reason to change.",
  },
  {
    topic: "SOLID principles",
    text: "Complete the Open Closed Principle: software should be open for ___ and closed for ___.",
    options: [
      "extension, modification",
      "modification, extension",
      "inheritance, composition",
      "reading, writing",
    ],
    why: "OCP slide: each piece of software should be open for extension and closed for modification.",
  },
  {
    topic: "SOLID principles",
    text: "Under the Open Closed Principle, how should new behavior be added?",
    options: [
      "By extending the code, without modifying its internals",
      "By editing the existing class directly",
      "By copying the class and changing the copy",
      "By adding more if/else branches to the existing method",
    ],
    why: "OCP slide: the behavior should be extended without needing to modify the internals.",
  },
  {
    topic: "SOLID principles",
    text: "Which statement describes the Liskov Substitution Principle?",
    options: [
      "Objects of a class can be replaced by instances of its subclasses without altering how the software works",
      "A class should have only one reason to change",
      "Classes should depend on abstractions, not on concrete classes",
      "A client should not implement methods it does not use",
    ],
    why: "LSP slide: objects of a class should be substitutable with instances of the existing subclasses, without altering the functionalities of the software.",
  },
  {
    topic: "SOLID principles",
    text: "Which statement describes the Interface Segregation Principle?",
    options: [
      "A client shouldn't be forced to implement an interface, or methods, that it doesn't use",
      "Every interface must have exactly one method",
      "Interfaces must be placed in a separate module",
      "A subclass must override every method of its parent",
    ],
    why: "ISP slide: a client shouldn't be forced to implement an interface, or methods from an interface, that it doesn't use.",
  },
  {
    topic: "SOLID principles",
    text: "What does the Interface Segregation Principle recommend for a large interface?",
    options: [
      "Split it into multiple smaller interfaces",
      "Merge it with other interfaces",
      "Replace it with a concrete class",
      "Give all its methods empty bodies",
    ],
    why: "ISP slide: it is recommended to split larger interfaces into multiple smaller ones.",
  },
  {
    topic: "SOLID principles",
    text: "Which statement describes the Dependency Inversion Principle?",
    options: [
      "Software entities must depend on abstractions, not on concrete things",
      "Low-level modules must call high-level modules directly",
      "A class should create all its dependencies itself",
      "Each module should be responsible for one thing",
    ],
    why: "DIP slide: software entities must depend on abstractions, not on concrete things.",
  },
  {
    topic: "SOLID principles",
    text: "According to the Dependency Inversion Principle, how should two modules on different levels relate?",
    options: [
      "They rely on abstractions, not directly on each other",
      "The high-level module uses the low-level class directly",
      "They share global variables",
      "They must never work together",
    ],
    why: "DIP slide: separate modules located on different levels must not depend directly on each other, but should rely on abstractions.",
  },
  {
    topic: "SOLID principles",
    text: "\"Being responsible only for one thing, it will have only one reason to change.\" Which principle is this?",
    options: [
      "Single Responsibility",
      "Open Closed",
      "Interface Segregation",
      "Dependency Inversion",
    ],
    why: "This sentence is from the Single Responsibility Principle slide.",
  },
  {
    topic: "SOLID principles",
    text: "\"The behavior should be extended without needing to modify the internals.\" Which principle is this?",
    options: [
      "Open Closed",
      "Liskov Substitution",
      "Single Responsibility",
      "Interface Segregation",
    ],
    why: "This sentence is from the Open Closed Principle slide.",
  },
  {
    topic: "SOLID principles",
    text: "Who wrote \"Design Principles and Design Patterns\" (2000) and \"Clean Code\" (2008), listed in the SOLID references?",
    options: [
      "Robert C. Martin",
      "The Gang of Four",
      "Barbara Liskov",
      "Bjarne Stroustrup",
    ],
    why: "References slide: Robert C. Martin, 2000, Design Principles and Design Patterns; Robert C. Martin, 2008, Clean Code.",
  },

  // ---------------- SOLID principles: code ----------------
  {
    topic: "SOLID principles",
    text: "Which SOLID principle does this class break?",
    code:
`class Report {
public:
    void addProblem(std::string text);
    void saveToFile(std::string path);
    void sendEmail(std::string to);
    void printPdf();
};`,
    options: [
      "Single Responsibility",
      "Liskov Substitution",
      "Interface Segregation",
      "Dependency Inversion",
    ],
    why: "Report stores problems, writes files, sends emails and prints PDFs. That is many responsibilities, so it has many reasons to change.",
  },
  {
    topic: "SOLID principles",
    text: "Every new shape means editing this function. Which principle is broken?",
    code:
`double area(const Shape& s) {
    if (s.type == "circle") return 3.14 * s.r * s.r;
    if (s.type == "square") return s.a * s.a;
    return 0;
}`,
    options: [
      "Open Closed",
      "Single Responsibility",
      "Interface Segregation",
      "Liskov Substitution",
    ],
    why: "The function is not closed for modification: to support a triangle you must change its internals instead of extending the code.",
  },
  {
    topic: "SOLID principles",
    text: "migrate() works for every Bird, but crashes when it gets a Penguin. Which principle is broken?",
    code:
`class Bird {
public:
    virtual void fly() { /* ... */ }
};
class Penguin : public Bird {
public:
    void fly() override { throw std::logic_error("can't fly"); }
};
void migrate(Bird& b) { b.fly(); }`,
    options: [
      "Liskov Substitution",
      "Open Closed",
      "Dependency Inversion",
      "Single Responsibility",
    ],
    why: "A Penguin cannot replace a Bird without changing how the program works, so the subclass is not substitutable.",
  },
  {
    topic: "SOLID principles",
    text: "Robot leaves eat() and sleep() empty. Which principle is broken?",
    code:
`class Worker {
public:
    virtual void work() = 0;
    virtual void eat() = 0;
    virtual void sleep() = 0;
};
class Robot : public Worker {
public:
    void work() override { /* ... */ }
    void eat() override {}    // robots don't eat
    void sleep() override {}  // robots don't sleep
};`,
    options: [
      "Interface Segregation",
      "Liskov Substitution",
      "Open Closed",
      "Dependency Inversion",
    ],
    why: "Robot is forced to implement methods it doesn't use. The fix from the slides: split Worker into multiple smaller interfaces.",
  },
  {
    topic: "SOLID principles",
    text: "Which principle does ReportService break?",
    code:
`class MySqlDatabase {
public:
    void save(std::string data);
};
class ReportService {
    MySqlDatabase db;   // a concrete class
public:
    void submit(std::string report) { db.save(report); }
};`,
    options: [
      "Dependency Inversion",
      "Interface Segregation",
      "Liskov Substitution",
      "Single Responsibility",
    ],
    why: "ReportService (high level) depends directly on MySqlDatabase (low level, concrete) instead of an abstraction.",
  },
  {
    topic: "SOLID principles",
    text: "ReportService keeps a MySqlDatabase object inside it and calls db.save(). How do you fix it according to the Dependency Inversion Principle?",
    options: [
      "Make ReportService use an abstract Storage interface that MySqlDatabase implements",
      "Make ReportService inherit from MySqlDatabase",
      "Copy the save() code into ReportService",
      "Make MySqlDatabase a global variable",
    ],
    why: "DIP: depend on abstractions. ReportService keeps a Storage& and any database class can implement Storage.",
  },
  {
    topic: "SOLID principles",
    text: "Dispatcher only knows Notifier, not EmailNotifier or SmsNotifier. Which principle does this show?",
    code:
`class Notifier {
public:
    virtual void send(std::string msg) = 0;
    virtual ~Notifier() = default;
};
class EmailNotifier : public Notifier { /* ... */ };
class SmsNotifier   : public Notifier { /* ... */ };

class Dispatcher {
    Notifier& notifier;
public:
    Dispatcher(Notifier& n) : notifier(n) {}
    void alert(std::string msg) { notifier.send(msg); }
};`,
    options: [
      "Dependency Inversion",
      "Interface Segregation",
      "Single Responsibility",
      "Open Closed",
    ],
    why: "Dispatcher depends on the abstraction Notifier, not on the concrete classes.",
  },
  {
    topic: "SOLID principles",
    text: "With this design, a new PushNotifier class can be added without changing Dispatcher. Which principle does that show?",
    code:
`class Notifier {
public:
    virtual void send(std::string msg) = 0;
    virtual ~Notifier() = default;
};
class PushNotifier : public Notifier { /* new */ };

class Dispatcher {
    Notifier& notifier;
public:
    Dispatcher(Notifier& n) : notifier(n) {}
    void alert(std::string msg) { notifier.send(msg); }
};`,
    options: [
      "Open Closed",
      "Interface Segregation",
      "Single Responsibility",
      "Liskov Substitution",
    ],
    why: "The behavior is extended (a new notifier) without modifying the internals of Dispatcher: open for extension, closed for modification.",
  },

  // ---------------- Creational patterns: theory ----------------
  {
    topic: "Creational patterns",
    text: "What are creational design patterns all about?",
    options: [
      "Class instantiation (creating objects)",
      "Combining classes into bigger structures",
      "How objects send messages to each other",
      "Saving objects into a database",
    ],
    why: "Overview slide: the Creational Design Patterns are all about class instantiation.",
  },
  {
    topic: "Creational patterns",
    text: "Into which two groups are creational patterns divided?",
    options: [
      "Class-creation patterns and object-creation patterns",
      "Static patterns and dynamic patterns",
      "Simple patterns and complex patterns",
      "Interface patterns and implementation patterns",
    ],
    why: "Overview slide: Class-Creation patterns and Object-Creation patterns.",
  },
  {
    topic: "Creational patterns",
    text: "What do class-creation patterns use?",
    options: ["Inheritance", "Delegation", "Global variables", "Templates"],
    why: "Overview slide: Class-Creation patterns use inheritance, Object-Creation patterns use delegation.",
  },
  {
    topic: "Creational patterns",
    text: "What do object-creation patterns use?",
    options: ["Delegation", "Inheritance", "Macros", "Only static methods"],
    why: "Overview slide: Object-Creation patterns use delegation, Class-Creation patterns use inheritance.",
  },
  {
    topic: "Creational patterns",
    text: "What is the Singleton pattern?",
    options: [
      "A class that should have only one instance at any time",
      "A class that has only one method",
      "A class that can be inherited only once",
      "A class that creates one object of every other class",
    ],
    why: "Singleton slide: a class that should have only one instance at any time.",
  },
  {
    topic: "Creational patterns",
    text: "In a Singleton, what should the constructor be?",
    options: ["Private", "Public", "Virtual", "Explicit"],
    why: "Singleton slide: the constructor should be private, so nobody outside can create another instance.",
  },
  {
    topic: "Creational patterns",
    text: "Where does a Singleton keep its one instance?",
    options: [
      "In a static, encapsulated member of the class itself",
      "In a global variable outside the class",
      "In every object that uses it",
      "In a file on disk",
    ],
    why: "Singleton slide: it contains a static encapsulated instance. In the UML diagram it is called uniqueInstance.",
  },
  {
    topic: "Creational patterns",
    text: "Besides the private constructor and the static instance, what else do the slides require from a Singleton?",
    options: [
      "It must be made thread safe",
      "It must be copyable",
      "It must have a public constructor for tests",
      "It must inherit from an abstract class",
    ],
    why: "Singleton slide: it must be made thread safe.",
  },
  {
    topic: "Creational patterns",
    text: "In the Singleton UML diagram, what does the static Instance() method return?",
    options: [
      "uniqueInstance",
      "A new Singleton every time",
      "singletonData",
      "A copy of the Singleton",
    ],
    why: "The note next to Instance() in the diagram says: return uniqueInstance.",
  },
  {
    topic: "Creational patterns",
    text: "What is the main idea of the Prototype pattern?",
    options: [
      "Already initialized instances that are meant to be cloned",
      "A class that has only one instance",
      "Building an object step by step",
      "A first draft of a class that is replaced later",
    ],
    why: "Prototype slide: initialized instances of the classes that are meant to be cloned.",
  },
  {
    topic: "Creational patterns",
    text: "Besides the prototype objects, what else does the Prototype pattern use (according to the slides)?",
    options: [
      "A collection that caches the prototype objects",
      "A Director that controls the building steps",
      "A private constructor and a static instance",
      "A family of related factories",
    ],
    why: "Prototype slide: a collection that caches the prototype objects.",
  },
  {
    topic: "Creational patterns",
    text: "In the Prototype UML diagram, how does the Client get a new object?",
    options: [
      "p = prototype->Clone()",
      "p = new ConcretePrototype1()",
      "p = Prototype::Instance()",
      "p = builder->GetResult()",
    ],
    why: "The note under Client::Operation() in the diagram: p = prototype->Clone().",
  },
  {
    topic: "Creational patterns",
    text: "In the Prototype UML diagram, what does Clone() in ConcretePrototype1 return?",
    options: [
      "A copy of itself",
      "A new empty object of the base class",
      "The same object (the same pointer)",
      "A ConcretePrototype2 object",
    ],
    why: "The note under each ConcretePrototype's Clone() in the diagram: return copy of self.",
  },
  {
    topic: "Creational patterns",
    text: "What does the Factory Method pattern do?",
    options: [
      "Creates an instance out of several related derived classes",
      "Makes sure a class has only one instance",
      "Copies an existing object",
      "Separates object construction from its representation",
    ],
    why: "Factory Method slide: creates an instance out of several related derived classes.",
  },
  {
    topic: "Creational patterns",
    text: "According to the slides, how is Factory Method usually used?",
    options: [
      "Together with other creational design patterns",
      "Alone, never with other patterns",
      "Only in multi-threaded programs",
      "Only inside a Singleton",
    ],
    why: "Factory Method slide: it is usually used together with other creational design patterns.",
  },
  {
    topic: "Creational patterns",
    text: "In the Factory Method UML diagram, which class overrides FactoryMethod() to return new ConcreteProduct?",
    options: ["ConcreteCreator", "Creator", "Product", "Client"],
    why: "In the diagram, ConcreteCreator::FactoryMethod() has the note: return new ConcreteProduct.",
  },
  {
    topic: "Creational patterns",
    text: "In the Factory Method UML diagram, how does Creator's AnOperation() get a product?",
    options: [
      "It calls FactoryMethod()",
      "It calls new ConcreteProduct() directly",
      "It clones an existing product",
      "It asks a Director to build it",
    ],
    why: "The note next to AnOperation() in the diagram: product = FactoryMethod().",
  },
  {
    topic: "Creational patterns",
    text: "What does the Abstract Factory pattern provide?",
    options: [
      "An interface for creating families of related objects without specifying the concrete object",
      "One single instance of a factory",
      "A way to copy objects from a cache",
      "A step-by-step way to build one complex object",
    ],
    why: "Abstract Factory slide: provides an interface for creating families of related objects without specifying the concrete object.",
  },
  {
    topic: "Creational patterns",
    text: "How does an Abstract Factory create each type of product?",
    options: [
      "It defines a Factory Method for each type of product",
      "It uses one method with a big switch for all products",
      "It clones products from a cache",
      "It lets the client call the product constructors",
    ],
    why: "Abstract Factory slide: it defines Factory Methods for each type of product (CreateProductA(), CreateProductB() in the diagram).",
  },
  {
    topic: "Creational patterns",
    text: "In the Abstract Factory UML diagram, which products does ConcreteFactory1 create?",
    options: [
      "ProductA1 and ProductB1",
      "ProductA1 and ProductA2",
      "ProductA2 and ProductB2",
      "AbstractProductA and AbstractProductB",
    ],
    why: "Each concrete factory creates one family: ConcreteFactory1 makes ProductA1 and ProductB1, ConcreteFactory2 makes ProductA2 and ProductB2.",
  },
  {
    topic: "Creational patterns",
    text: "In the Abstract Factory UML diagram, which classes does the Client point to?",
    options: [
      "AbstractFactory, AbstractProductA and AbstractProductB",
      "ConcreteFactory1 and ConcreteFactory2",
      "ProductA1, ProductA2, ProductB1 and ProductB2",
      "Only ConcreteFactory1",
    ],
    why: "The Client's arrows go only to the abstract classes, so it never names a concrete factory or product.",
  },
  {
    topic: "Creational patterns",
    text: "What does the Builder pattern do?",
    options: [
      "Separates object construction from its representation, so the same construction process can create different representations",
      "Creates a family of related objects",
      "Keeps only one instance of a class",
      "Creates new objects by cloning",
    ],
    why: "Builder slide: separates object construction from its representation so that the same construction process could create different representations.",
  },
  {
    topic: "Creational patterns",
    text: "In the Builder UML diagram, what does the Director's Construct() method do?",
    options: [
      "Calls builder->BuildPart() for all objects in the structure",
      "Returns the finished Product",
      "Creates a ConcreteBuilder with new",
      "Clones the Product",
    ],
    why: "The note under Director::Construct(): for all objects in structure { builder->BuildPart() }.",
  },
  {
    topic: "Creational patterns",
    text: "In the Builder UML diagram, which class has GetResult() to give back the finished product?",
    options: ["ConcreteBuilder", "Director", "Builder", "Product"],
    why: "ConcreteBuilder has BuildPart() and GetResult(), and it is the one that creates the Product.",
  },
  {
    topic: "Creational patterns",
    text: "Which 1994 book by the \"Gang of Four\" is in the references of the creational patterns slides?",
    options: [
      "Design Patterns: Elements of Reusable Object-Oriented Software",
      "Clean Code",
      "Design Principles and Design Patterns",
      "The C++ Programming Language",
    ],
    why: "References slide: The \"Gang of four\", 1994, Design Patterns: Elements of Reusable Object-Oriented Software.",
  },
  {
    topic: "Creational patterns",
    text: "You keep a few ready, initialized objects in a collection and make new objects by copying them. Which pattern is this?",
    options: ["Prototype", "Singleton", "Builder", "Abstract Factory"],
    why: "Prototype: initialized instances meant to be cloned, kept in a collection that caches them.",
  },
  {
    topic: "Creational patterns",
    text: "The whole program must use one shared settings object, and nobody may create a second one. Which pattern fits?",
    options: ["Singleton", "Prototype", "Factory Method", "Builder"],
    why: "Singleton: a class that should have only one instance at any time.",
  },
  {
    topic: "Creational patterns",
    text: "The same construction steps should give different results (for example an HTML report or a plain text report). Which pattern fits?",
    options: ["Builder", "Singleton", "Prototype", "Abstract Factory"],
    why: "Builder: the same construction process can create different representations.",
  },

  // ---------------- Creational patterns: code ----------------
  {
    topic: "Creational patterns",
    text: "Which pattern is this?",
    code:
`class Logger {
    static Logger* instance;
    Logger() {}
public:
    static Logger* getInstance() {
        if (instance == nullptr)
            instance = new Logger();
        return instance;
    }
};`,
    options: ["Singleton", "Prototype", "Factory Method", "Builder"],
    why: "Private constructor + static encapsulated instance + a static method that returns it = Singleton.",
  },
  {
    topic: "Creational patterns",
    text: "Two threads call getInstance() at the same moment, both see nullptr, and two Loggers get created. Which Singleton requirement from the slides is missing?",
    code:
`class Logger {
    static Logger* instance;
    Logger() {}
public:
    static Logger* getInstance() {
        if (instance == nullptr)
            instance = new Logger();
        return instance;
    }
};`,
    options: [
      "It must be thread safe",
      "The constructor must be private",
      "The instance must be static",
      "The instance must be encapsulated",
    ],
    why: "The constructor is private and the instance is static and private, but nothing stops two threads from creating it at the same time.",
  },
  {
    topic: "Creational patterns",
    text: "What does the private constructor of Logger prevent?",
    code:
`class Logger {
    static Logger* instance;
    Logger() {}
public:
    static Logger* getInstance();
};`,
    options: [
      "Code outside the class from writing new Logger() or Logger l;",
      "getInstance() from creating the instance",
      "Other classes from calling getInstance()",
      "Logger from having any methods",
    ],
    why: "Only the class itself can call a private constructor, so the only way to get a Logger is getInstance().",
  },
  {
    topic: "Creational patterns",
    text: "Which pattern does clone() implement?",
    code:
`class Shape {
public:
    virtual Shape* clone() const = 0;
    virtual ~Shape() = default;
};
class Circle : public Shape {
    int radius;
public:
    Circle(int r) : radius(r) {}
    Shape* clone() const override { return new Circle(*this); }
};`,
    options: ["Prototype", "Singleton", "Builder", "Abstract Factory"],
    why: "Like Clone() in the Prototype diagram, each concrete class returns a copy of itself.",
  },
  {
    topic: "Creational patterns",
    text: "Compared with the Factory Method UML diagram, which role does RoadLogistics play?",
    code:
`class Transport {
public:
    virtual void deliver() = 0;
    virtual ~Transport() = default;
};
class Truck : public Transport { void deliver() override {} };

class Logistics {
public:
    virtual Transport* createTransport() = 0;
    void planDelivery() {
        Transport* t = createTransport();
        t->deliver();
        delete t;
    }
};
class RoadLogistics : public Logistics {
    Transport* createTransport() override { return new Truck(); }
};`,
    options: ["ConcreteCreator", "Creator", "ConcreteProduct", "Product"],
    why: "Logistics is the Creator, RoadLogistics is the ConcreteCreator, Transport is the Product and Truck is the ConcreteProduct.",
  },
  {
    topic: "Creational patterns",
    text: "In this code, which method is the factory method?",
    code:
`class Logistics {
public:
    virtual Transport* createTransport() = 0;
    void planDelivery() {
        Transport* t = createTransport();
        t->deliver();
        delete t;
    }
};
class RoadLogistics : public Logistics {
    Transport* createTransport() override { return new Truck(); }
};`,
    options: ["createTransport()", "planDelivery()", "deliver()", "the Truck constructor"],
    why: "createTransport() is FactoryMethod() and planDelivery() is AnOperation(), which calls it to get a product.",
  },
  {
    topic: "Creational patterns",
    text: "Which pattern is this?",
    code:
`class GUIFactory {
public:
    virtual Button*   createButton() = 0;
    virtual Checkbox* createCheckbox() = 0;
    virtual ~GUIFactory() = default;
};
class DarkFactory : public GUIFactory {
public:
    Button*   createButton()   override { return new DarkButton(); }
    Checkbox* createCheckbox() override { return new DarkCheckbox(); }
};
class LightFactory : public GUIFactory { /* LightButton, LightCheckbox */ };`,
    options: ["Abstract Factory", "Factory Method", "Builder", "Prototype"],
    why: "GUIFactory is an interface for creating a family of related objects (a matching button and checkbox), with one factory method per product type.",
  },
  {
    topic: "Creational patterns",
    text: "Compared with the Builder UML diagram, which role does Cook play?",
    code:
`class PizzaBuilder {
public:
    virtual void buildDough() = 0;
    virtual void buildSauce() = 0;
    virtual void buildTopping() = 0;
    virtual Pizza getResult() = 0;
    virtual ~PizzaBuilder() = default;
};
class Cook {
public:
    Pizza make(PizzaBuilder& b) {
        b.buildDough();
        b.buildSauce();
        b.buildTopping();
        return b.getResult();
    }
};`,
    options: ["Director", "ConcreteBuilder", "Product", "Builder"],
    why: "Cook runs the construction steps on whatever builder it gets, like Director::Construct() calling BuildPart(). PizzaBuilder is the Builder and Pizza is the Product.",
  },
];
