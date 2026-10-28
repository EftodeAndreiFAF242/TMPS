//Each piece of software should be open for extension and closed for modification.
//The behavior should be extended without needing to modify the internals.

//On screen: you type the category and description, and you may get Report refused: ...



// SOLID principle 2: Open/Closed Principle (OCP).


#pragma once

#include <string>
#include <vector>

struct Report;

// The common shape of every rule. New rules plug in here.
class Rule {
public:
    // A base class with virtual methods gets a virtual destructor.
    virtual ~Rule() {}

    // Returns an empty text if the report is fine, or the error message if it is not.
    // "= 0" means the method has no body here: every rule has to write its own.
    virtual std::string check(const Report& report) = 0;
};

// Rule: the category has to be one the city hall works with.
class CategoryRule : public Rule {
public:
    std::string check(const Report& report) override;
};

// Rule: the description has to say something.
class DescriptionRule : public Rule {
public:
    std::string check(const Report& report) override;
};

// Checks a report against every rule it was given.
class Validator {
public:
    void addRule(Rule* rule);

    // Returns the error messages. An empty list means the report is valid.
    std::vector<std::string> validate(const Report& report);

private:
    std::vector<Rule*> rules;
};
