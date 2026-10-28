// Glossary: the words used in the quiz and the slides, explained for beginners.
// Each group has a title and a list of words; "code" is an optional small C++ example.

const GLOSSARY = [
  {
    title: "Object-oriented basics",
    words: [
      {
        word: "OOP (object-oriented programming)",
        text: "A way of writing programs where the code is organized into classes and objects. Each object keeps its data together with the functions that work on that data. SOLID and design patterns are rules and ideas for writing good OOP code.",
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
        text: "A real thing made from a class, living in memory with its own data. From one class you can make many objects: Circle a(1); and Circle b(5); are two different circles.",
      },
      {
        word: "Instance",
        text: "Another word for object. \"An instance of Circle\" means \"an object made from the Circle class\". A Singleton is a class that allows only one instance.",
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
        text: "A variable that belongs to an object, for example radius in Circle. In the Singleton UML diagram, uniqueInstance and singletonData are attributes.",
      },
      {
        word: "Method (member function)",
        text: "A function that belongs to a class and works with the object's data, for example area() or clone(). In UML diagrams methods are written with (), like Clone().",
      },
      {
        word: "Constructor",
        text: "A special method with the same name as the class. It runs automatically when an object is created and prepares the object's data.",
        code:
`class Circle {
    int radius;
public:
    Circle(int r) : radius(r) {}   // constructor
};`,
      },
      {
        word: "Destructor",
        text: "A special method named like the class with a ~ in front (~Shape). It runs automatically when an object is destroyed. \"virtual ~Shape() = default;\" in a base class makes sure the right destructor runs when you delete a subclass object through a base class pointer.",
      },
      {
        word: "public, private, protected",
        text: "They say who can use a member of a class. public: everyone. private: only the class itself. protected: the class and its subclasses. A Singleton's constructor is private, so code outside the class cannot create objects.",
      },
      {
        word: "Encapsulation (encapsulated)",
        text: "Hiding an object's data inside the class (making it private), so other code can use it only through the class's methods. The Singleton's instance is \"static encapsulated\": it is hidden inside the class and you reach it only through getInstance().",
      },
      {
        word: "static",
        text: "A static member belongs to the class itself, not to one object. There is only one copy of it, shared by everyone. A static method can be called without any object, using the class name: Logger::getInstance().",
      },
      {
        word: "Inheritance",
        text: "When a class is built on top of another class and gets its data and methods. It describes an \"is a\" relation: a Circle is a Shape.",
        code:
`class Shape { /* ... */ };
class Circle : public Shape { /* ... */ };  // Circle inherits from Shape`,
      },
      {
        word: "Base class (parent class, superclass)",
        text: "The class that other classes inherit from. Shape is the base class of Circle.",
      },
      {
        word: "Derived class (subclass, child class)",
        text: "A class that inherits from another class. Circle is a derived class of Shape. \"Several related derived classes\" (Factory Method slide) means several subclasses of the same base class.",
      },
      {
        word: "virtual",
        text: "A keyword that lets a subclass replace a method of the base class. When you call the method through a base class pointer or reference, the subclass's version runs.",
      },
      {
        word: "override",
        text: "Written after a method in a subclass. It means \"this replaces the virtual method from the base class\". The compiler checks that such a method really exists in the base class.",
      },
      {
        word: "Pure virtual method (= 0)",
        text: "A virtual method with no code in the base class, written with = 0 at the end. Every concrete subclass must write the code for it.",
        code: `virtual Shape* clone() const = 0;   // pure virtual`,
      },
      {
        word: "Abstract class",
        text: "A class with at least one pure virtual method. You cannot create objects of it directly; it only says what its subclasses must do. Shape and Logistics are abstract classes. In UML diagrams abstract names are written in italics (Product, Creator, Builder).",
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
        text: "To write the real code of a method that was only declared. \"Implementing an interface\" means inheriting from it and writing the code for all its methods. Robot implements work(), eat() and sleep() from Worker.",
      },
      {
        word: "Concrete class",
        text: "A normal class where every method has code, so you can create objects of it. The opposite of abstract. In the diagrams: ConcreteProduct, ConcreteCreator, ConcreteBuilder. \"Depending on concrete things\" means using one specific class directly, like ReportService using MySqlDatabase.",
      },
      {
        word: "Abstraction",
        text: "Looking at what something does, not at how it does it. In code, an abstraction is usually an interface or an abstract class (Notifier), and the details are in concrete classes (EmailNotifier, SmsNotifier).",
      },
      {
        word: "Polymorphism",
        text: "\"Many forms\": the same call does different things depending on the real object. notifier.send(msg) sends an email or an SMS depending on which Notifier was given. It works through virtual methods.",
      },
      {
        word: "Composition",
        text: "Building a class from other objects that it keeps as members (a \"has a\" relation). ReportService has a MySqlDatabase inside it. It is the main alternative to inheritance.",
      },
      {
        word: "Delegation",
        text: "When an object gives a job to another object instead of doing it itself. Dispatcher delegates the sending to notifier.send(). Object-creation patterns use delegation: another object (a factory, a builder, a prototype) does the creating.",
      },
      {
        word: "Client",
        text: "The code that uses a class or an interface. In the diagrams, Client is the code that asks for new objects, for example by calling prototype->Clone() or by using an AbstractFactory.",
      },
      {
        word: "Dependency (depends on)",
        text: "Class A depends on class B when A uses B: it keeps a B, calls B's methods, or creates a B. If B changes, A may have to change too. ReportService depends on MySqlDatabase.",
      },
      {
        word: "Module",
        text: "A part of a program that groups related code, for example a file, a group of classes or a library.",
      },
      {
        word: "High-level and low-level modules",
        text: "High-level modules hold the main logic of the program (ReportService: what to do with a report). Low-level modules handle the details (MySqlDatabase: how to save the data). The Dependency Inversion Principle says both should depend on an abstraction between them.",
      },
    ],
  },
  {
    title: "C++ words from the code",
    words: [
      {
        word: "Pointer (*), new, delete, nullptr",
        text: "Logger* p holds the address of a Logger object in memory. new Logger() creates an object and gives back its address. delete p destroys that object. nullptr means the pointer points to nothing yet.",
        code:
`Logger* p = nullptr;   // points to nothing
p = new Logger();      // now points to a new Logger
delete p;              // destroy it`,
      },
      {
        word: "Reference (&)",
        text: "Another name for an object that already exists, written Type&. In migrate(Bird& b) the function works with the original bird, not a copy. A base class reference can refer to an object of any subclass.",
      },
      {
        word: "this, *this and copying",
        text: "this is a pointer to the current object, so *this is the object itself. new Circle(*this) creates a new Circle that is a copy of the current one. That is how clone() makes a copy.",
      },
      {
        word: "Exception (throw)",
        text: "throw std::logic_error(\"...\") stops the normal work of the program and reports an error. If no code catches it, the program crashes. That is what happens with Penguin::fly() in the Liskov example.",
      },
    ],
  },
  {
    title: "SOLID principles",
    words: [
      {
        word: "Design principle",
        text: "A general rule for good design. It does not give you ready code; it tells you what good code should look like. SOLID is a set of 5 such principles.",
      },
      {
        word: "SOLID",
        text: "An acronym (a word made from first letters) for 5 OOP design principles: Single Responsibility, Open Closed, Liskov Substitution, Interface Segregation, Dependency Inversion.",
      },
      {
        word: "Maintainable, testable, extendable",
        text: "The goals of SOLID. Maintainable code is easy to fix and change later. Testable code is easy to check with tests. Extendable code is easy to add new features to.",
      },
      {
        word: "Responsibility (reason to change)",
        text: "A responsibility is one job a piece of code does, like storing reports, saving files or sending emails. Every job is a possible reason to change that code, so one job means one reason to change.",
      },
      {
        word: "Single Responsibility Principle (SRP)",
        text: "Every module, class or function should do one job only, so it has only one reason to change.",
      },
      {
        word: "Extension and modification",
        text: "Extension means adding new behavior by adding new code, for example a new subclass. Modification means editing code that already works. The Open Closed Principle says: allow extension, avoid modification.",
      },
      {
        word: "Open Closed Principle (OCP)",
        text: "Code should be open for extension and closed for modification: you add new features without editing the classes that already work.",
      },
      {
        word: "Substitutable",
        text: "Can be put in the place of something else and still work. A subclass object is substitutable for its base class if the code using the base class keeps working with it.",
      },
      {
        word: "Liskov Substitution Principle (LSP)",
        text: "Objects of a class should be replaceable by objects of its subclasses without breaking the program. If code works with a Bird, it must also work with every subclass of Bird. It is named after Barbara Liskov.",
      },
      {
        word: "Interface Segregation Principle (ISP)",
        text: "Segregation means separation. A class should not be forced to implement methods it does not use, so big interfaces should be split into smaller ones.",
      },
      {
        word: "Dependency Inversion Principle (DIP)",
        text: "Inversion means turning around. Classes should depend on abstractions (interfaces), not on concrete classes. Instead of a high-level class using a low-level class directly, both depend on an interface between them.",
      },
    ],
  },
  {
    title: "Creational design patterns",
    words: [
      {
        word: "Design pattern",
        text: "A known, reusable solution to a problem that appears often in software design. It is a plan for how to organize classes, not ready code you copy.",
      },
      {
        word: "Gang of Four (GoF)",
        text: "The four authors (Gamma, Helm, Johnson, Vlissides) of the 1994 book \"Design Patterns: Elements of Reusable Object-Oriented Software\". The slides' diagrams come from their style.",
      },
      {
        word: "Creational design patterns",
        text: "Patterns about how objects are created: Singleton, Prototype, Factory Method, Abstract Factory and Builder.",
      },
      {
        word: "Class-creation and object-creation patterns",
        text: "Class-creation patterns use inheritance: a subclass decides which object is created (Factory Method). Object-creation patterns use delegation: another object does the creating (Abstract Factory, Builder, Prototype, Singleton).",
      },
      {
        word: "Singleton",
        text: "A class that allows only one instance and gives everyone access to it through a static method. Its constructor is private and the instance is stored in a static member.",
      },
      {
        word: "Thread (thread safe)",
        text: "A thread is one line of execution; a program can run several threads at the same time. Thread safe code works correctly even when several threads use it at once. A Singleton that is not thread safe may create two instances if two threads ask for it at the same moment.",
      },
      {
        word: "Prototype",
        text: "A pattern where new objects are made by copying (cloning) an existing object that is already set up, instead of building them from zero.",
      },
      {
        word: "Clone",
        text: "To make a copy of an object. clone() returns a new object with the same data as the original.",
      },
      {
        word: "Cache",
        text: "A place where things are kept ready so they can be reused quickly. In Prototype, a collection keeps the prototype objects ready to be cloned.",
      },
      {
        word: "Factory",
        text: "A class or method whose job is to create objects, so the rest of the code does not have to call new on concrete classes itself.",
      },
      {
        word: "Factory Method",
        text: "A method in a base class that creates an object. Subclasses override it to decide which concrete class gets created.",
      },
      {
        word: "Product and ConcreteProduct",
        text: "In design patterns, the product is the object being created. Product is the abstract type, ConcreteProduct is the real class that gets created (Transport and Truck).",
      },
      {
        word: "Creator and ConcreteCreator",
        text: "In Factory Method: Creator is the base class that declares FactoryMethod() and uses it (Logistics). ConcreteCreator is the subclass that overrides it and returns a ConcreteProduct (RoadLogistics).",
      },
      {
        word: "Abstract Factory",
        text: "An interface with one create method for each product type, used to create a whole family of objects that belong together, without naming their concrete classes.",
      },
      {
        word: "Family of related objects",
        text: "Objects made to work together, like a DarkButton and a DarkCheckbox. An Abstract Factory makes sure all the objects you get are from the same family.",
      },
      {
        word: "Builder",
        text: "A pattern that builds a complex object step by step. The same steps can produce different results (different representations).",
      },
      {
        word: "Director",
        text: "In Builder: the class that knows the order of the steps and calls them on a builder (Cook in the pizza example).",
      },
      {
        word: "ConcreteBuilder",
        text: "In Builder: a subclass of Builder that does each step its own way and gives back the finished product with GetResult().",
      },
      {
        word: "Representation",
        text: "The final form of the built object. In Builder, the same construction process (the same steps) can give different representations, for example an HTML report or a plain text report.",
      },
    ],
  },
  {
    title: "Reading the UML diagrams",
    words: [
      {
        word: "UML (class diagram)",
        text: "UML (Unified Modeling Language) is a standard way to draw software designs. The slides use class diagrams, which show classes and how they are connected.",
      },
      {
        word: "Class box",
        text: "Each class is drawn as a box: the name on top, then its methods and data. A name written in italics means an abstract class or a pure virtual method.",
      },
      {
        word: "Triangle arrow (inheritance)",
        text: "A line ending with a hollow triangle goes from a subclass to its base class. For example ConcreteCreator to Creator means ConcreteCreator inherits from Creator.",
      },
      {
        word: "Dashed arrow (creates)",
        text: "A dashed line with an arrow means one class creates objects of the other. ConcreteCreator to ConcreteProduct: ConcreteCreator creates ConcreteProducts.",
      },
      {
        word: "Solid arrow (has a reference)",
        text: "A solid line with an arrow means one class keeps and uses an object of the other. Client to Prototype: the Client keeps a prototype.",
      },
      {
        word: "Diamond (part of)",
        text: "A line that starts with a hollow diamond means one object holds the other as a part. Director to Builder: the Director holds a builder.",
      },
      {
        word: "Note",
        text: "A box with a folded corner, linked by a dashed line to a method. It shows what the method does, for example \"return uniqueInstance\".",
      },
    ],
  },
];
