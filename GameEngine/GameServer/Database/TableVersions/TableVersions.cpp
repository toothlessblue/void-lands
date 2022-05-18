//
// Created by ellis on 18/05/22.
//

#include <cppconn/statement.h>
#include <cppconn/resultset.h>
#include <string>
#include "TableVersions.h"
#include "../Database.h"

const unsigned int Database::TableVersions::VERSION;
constexpr const char* Database::TableVersions::NAME;
constexpr const char* Database::TableVersions::COLUMNS[];

unsigned int Database::TableVersions::getColumnCount() {
    return (sizeof Database::TableVersions::COLUMNS) / (sizeof Database::TableVersions::COLUMNS[0]);
}

const char* const* Database::TableVersions::getColumns() {
    return TableVersions::COLUMNS;
}

const char* Database::TableVersions::getName() {
    return TableVersions::NAME;
}

unsigned int Database::TableVersions::getVersion() {
    return Database::TableVersions::VERSION;
}

unsigned int Database::TableVersions::getVersion(const char* tableName) {
    sql::Statement* statement = Database::connection->createStatement();
    std::string query = std::string("SELECT * FROM TableVersions WHERE tableName=\"") + tableName + "\";";
    sql::ResultSet* result = statement->executeQuery(query);

    unsigned int version = 0;

    if (result->next()) {
        version = result->getUInt("version");
    }

    delete result;
    delete statement;

    return version;
}

void Database::TableVersions::setVersion(const char* tableName, unsigned int version) {
    sql::Statement* statement = Database::connection->createStatement();
    statement->execute("INSERT INTO TableVersions VALUES (\"TableVersions\", 1);");

    delete statement;
}
