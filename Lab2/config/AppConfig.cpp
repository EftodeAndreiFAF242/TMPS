// Lab 2 - Singleton: the class that has only one instance, the settings of the application

#include "Lab2/config/AppConfig.h"

#include <iostream>

using namespace std;

const AppConfig& AppConfig::getInstance() {
    // Made at the first call, then the same object every time.
    // C++ makes sure of this even when two threads call it at the same moment.
    static AppConfig instance;
    return instance;
}

AppConfig::AppConfig() {
    // For now the values are written here. Later they can be read from a file,
    // and only this constructor will change.
    defaultPriority = "Normal";
    defaultDeadlineDays = 7;
    truckCount = 2;

    cout << "[config] The settings were loaded.\n";
}

const string& AppConfig::getDefaultPriority() const {
    return defaultPriority;
}

int AppConfig::getDefaultDeadlineDays() const {
    return defaultDeadlineDays;
}

int AppConfig::getTruckCount() const {
    return truckCount;
}
