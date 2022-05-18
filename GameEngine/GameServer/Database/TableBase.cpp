//
// Created by ellis on 18/05/22.
//

#include "TableBase.h"
#include "Database.h"
#include "TableVersions/TableVersions.h"
#include <cppconn/statement.h>
#include <string>

unsigned int Database::TableBase::getVersion() {
    return 0;
}

const char* const* Database::TableBase::getColumns() {
    return nullptr;
}

const char* Database::TableBase::getName() {
    return nullptr;
}

unsigned int Database::TableBase::getColumnCount() {
    return 0;
}

void Database::TableBase::initialiseTable() {
    unsigned int version = Database::TableVersions::getVersion(this->getName());

    if (version == 0) {
        this->createTable();
    } else if (version < this->getVersion()) {
        this->updateTable();
    }
}

void Database::TableBase::createTable() {
    const char* const* columns = this->getColumns();
    unsigned int count = this->getColumnCount();

    std::string query = std::string("CREATE TABLE ") + this->getName() + " (";
    for (unsigned int i = 0; i < count; i++) {
        query += columns[i];
        query += ",";
    }
    query.pop_back(); // remove trailing comma
    query += ");";

    sql::Statement* statement = Database::connection->createStatement();
    statement->execute(query);

    Database::TableVersions::setVersion(this->getName(), this->getVersion());

    delete statement;
}

void Database::TableBase::updateTable() {

}