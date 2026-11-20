// Lab 3 - Flyweight: the Flyweight Factory, gives the same MarkerStyle every time for the same category

#include "Lab3/map/MarkerStyleFactory.h"

using namespace std;

const MarkerStyle* MarkerStyleFactory::get(const string& category) {
    // Look it up, or make it: a new style is made only the first time a category is asked for.
    if (styles.count(category) == 0) {
        styles[category] = make_unique<MarkerStyle>(category);
    }
    return styles[category].get();
}

int MarkerStyleFactory::count() const {
    return styles.size();
}
