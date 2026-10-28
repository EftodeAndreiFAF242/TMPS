//A class that should have only one instance at any time.
//It contains static encapsulated instance.
//The constructor should be private.
//It must be made thread safe.

#pragma once

#include "Lab1/SingleResponsibility.h"

class Database {
public:
    static Database& getInstance();

    Database(const Database&) = delete;
    Database& operator=(const Database&) = delete;

    ReportStorage* getStorage();

private:
    Database();

    ReportStorage storage;
};
