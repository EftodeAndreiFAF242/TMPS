// Lab 3 - Flyweight: the Flyweight, the look of the markers of one category, shared by all of them

#include "Lab3/map/MarkerStyle.h"

#include <iostream>

using namespace std;

MarkerStyle::MarkerStyle(const string& category) : category(category), icon(ICON_SIZE) {
    // The console can't show pictures, so here the icon is only memory filled with zeros. A real
    // map would load the picture of the category from a file at this point.
    cout << "[map] The icon of \"" << category << "\" was loaded.\n";
}

void MarkerStyle::draw(int reportId, const string& address) const {
    cout << "  [" << category << "] report #" << reportId << " at " << address << "\n";
}
