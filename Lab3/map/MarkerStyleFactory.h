// Lab 3 - Flyweight: the Flyweight Factory, gives the same MarkerStyle every time for the same category

#pragma once

#include <map>
#include <memory>
#include <string>

#include "Lab3/map/MarkerStyle.h"

// Makes each MarkerStyle only once. Asked for a category, it returns the style it already has, or
// makes it the first time that category is asked for.
class MarkerStyleFactory {
public:
    const MarkerStyle* get(const std::string& category);

    // How many different styles were made.
    int count() const;

private:
    std::map<std::string, std::unique_ptr<MarkerStyle>> styles;  // the category and its style
};
