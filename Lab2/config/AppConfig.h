// Lab 2 - Singleton: the class that has only one instance, the settings of the application

#pragma once

#include <string>

// The settings of the application. There is only one set of settings: it is made the first
// time someone asks for it, and after that it can only be read, never changed.
class AppConfig {
public:
    static const AppConfig& getInstance();

    AppConfig(const AppConfig&) = delete;
    AppConfig& operator=(const AppConfig&) = delete;

    // The priority a work order gets when nobody gives one.
    const std::string& getDefaultPriority() const;

    // The deadline, in days, a work order gets when nobody gives one.
    int getDefaultDeadlineDays() const;

    // How many trucks city hall has.
    int getTruckCount() const;

private:
    AppConfig();

    std::string defaultPriority;
    int defaultDeadlineDays;
    int truckCount;
};
