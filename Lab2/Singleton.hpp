// Singleton.hpp
//
// Creational pattern 1: Singleton.
// "A class has only one object, and the whole program reaches it from one place."
//
// The application has to keep every report in one place. If two parts of the program
// each made their own ReportStorage, a report saved by one part would be missing in the other.
// So the storage lives inside Database, and the program can't make a second Database.
//
// What stops a second Database from being made:
//   - the constructor is private, so "Database db;" does not compile outside the class
//   - copying is forbidden, so the one database can't be duplicated
//   - getInstance() is the only way to reach it, and it always returns the same object

#pragma once

#include "../Lab1/SingleResponsibility.hpp"  // for ReportStorage

class Database {
public:
    // The only way to get the database. "static" means it is called on the class itself:
    // Database::getInstance(), without having an object first.
    static Database& getInstance() {
        // A static variable inside a function is made the first time the function runs
        // and stays alive until the program ends. Every later call returns that same object.
        static Database instance;
        return instance;
    }

    // Copying is forbidden. Without these two lines,
    // "Database copy = Database::getInstance();" would make a second database.
    Database(const Database& other) = delete;
    void operator=(const Database& other) = delete;

    // The one storage of the application. It is a pointer, so it can be given
    // to the classes from lab 1, like ReportService.
    ReportStorage* getStorage() {
        return &storage;
    }

private:
    // Private: only getInstance() can make a Database.
    // The message shows on the screen how many times a database is made.
    Database() {
        cout << "[database] The database was created.\n";
    }

    ReportStorage storage;
};
