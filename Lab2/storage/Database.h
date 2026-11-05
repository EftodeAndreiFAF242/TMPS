#pragma once

#include "Lab1/storage/ReportStorage.h"

// The one database of the application. It is made the first time someone asks for it,
// and every later call returns the same object.
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
