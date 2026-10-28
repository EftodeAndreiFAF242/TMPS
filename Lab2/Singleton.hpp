//A class that should have only one instance at any time.
//It contains static encapsulated instance.
//The constructor should be private.
//It must be made thread safe.

#pragma once

#include "../Lab1/SingleResponsibility.hpp"

class Database {
public:
    static Database& getInstance() {
        static Database instance;
        return instance;
    }

    Database(const Database&) = delete;
    Database& operator=(const Database&) = delete;

    ReportStorage* getStorage() {
        return &storage;
    }

private:
    Database() {
        cout << "[database] The database was created.\n";
    }

    ReportStorage storage;
};
