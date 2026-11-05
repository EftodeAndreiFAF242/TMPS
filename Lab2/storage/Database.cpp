// Lab 2 - Singleton: the class that has only one instance

#include "Lab2/storage/Database.h"

#include <iostream>

using namespace std;

// TODO (teacher feedback): the singleton should not be the database.
// Use it for the configuration of the application instead.

Database& Database::getInstance() {
    static Database instance;
    return instance;
}

ReportStorage* Database::getStorage() {
    return &storage;
}

Database::Database() {
    cout << "[database] The database was created.\n";
}
