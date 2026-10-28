#include "Lab2/Singleton.h"

#include <iostream>

using namespace std;

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
