//
// Created by ellis on 17/05/22.
//

#include "Database.h"
#include "Entities/Entities.h"
#include "TableVersions/TableVersions.h"
#include <vector>

sql::Driver* Database::driver;
sql::Connection* Database::connection;
std::vector<const Database::TableBase*> Database::tables;

void Database::initialise() {
    Database::driver = get_driver_instance();
    Database::connection = driver->connect("127.0.0.1:3306", "server", "7Q*eH-b_5su.8mBV");
    Database::connection->setSchema("db");

    Database::addTable(Database::TableVersions::getInstance());
    Database::addTable(Database::Entities::getInstance());
}

void Database::destruct() {
    delete Database::connection;
    Database::tables.clear();
}

void Database::addTable(Database::TableBase* table) {
    Database::tables.push_back(table);
    table->initialiseTable();
}

std::vector<char*> Database::getTableColumns(const char* tableName) {
    return {};
}
