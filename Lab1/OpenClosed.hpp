// OpenClosed.hpp
//
// SOLID principle 2: Open/Closed Principle (OCP).
// "Code should be open for extension and closed for modification."
//
// The Validator checks a report against a list of rules.
// To add a new rule we write a new class that inherits from Rule.
// We do not change the Validator and we do not change the rules that already exist.
//
// The wrong way would be one function full of "if" statements, which has to be
// edited every time a rule is added.

#pragma once

#include "SingleResponsibility.hpp"  // for Report, string and vector

// The common shape of every rule. New rules plug in here.
class Rule {
public:
    // A base class with virtual methods gets a virtual destructor.
    virtual ~Rule() {}

    // Returns an empty text if the report is fine, or the error message if it is not.
    // "= 0" means the method has no body here: every rule has to write its own.
    virtual string check(const Report& report) = 0;
};

// Rule: the category has to be one the city hall works with.
class CategoryRule : public Rule {
public:
    string check(const Report& report) override {
        if (report.category == "Pothole" || report.category == "Street light" || report.category == "Garbage") {
            return "";
        }
        return "\"" + report.category + "\" is not a known category.";
    }
};

// Rule: the description has to say something.
class DescriptionRule : public Rule {
public:
    string check(const Report& report) override {
        if (report.description.length() >= 10) {
            return "";
        }
        return "The description must have at least 10 characters.";
    }
};

// Checks a report against every rule it was given.
class Validator {
public:
    void addRule(Rule* rule) {
        rules.push_back(rule);
    }

    // Returns the error messages. An empty list means the report is valid.
    vector<string> validate(const Report& report) {
        vector<string> errors;
        // The loop does not know which rules it runs. That is why a new rule needs no change here.
        for (Rule* rule : rules) {
            string error = rule->check(report);
            if (error != "") {
                errors.push_back(error);
            }
        }
        return errors;
    }

private:
    vector<Rule*> rules;
};
