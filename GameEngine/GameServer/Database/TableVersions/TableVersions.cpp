//
// Created by ellis on 18/05/22.
//

#include <cppconn/statement.h>
#include <cppconn/resultset.h>
#include <string>
#include "TableVersions.h"
#include "../Database.h"

namespace Database {
    TableVersions TableVersions::instance;

    TableVersions* TableVersions::getInstance() {
        return &TableVersions::instance;
    }

    unsigned int TableVersions::getVersion(const char* tableName) {
        if (!TableVersions::getInstance()->existsInDatabase()) return 0;

        sql::Statement* statement = connection->createStatement();
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

    void TableVersions::setVersion(const char* tableName, unsigned int version) {
        sql::Statement* statement = connection->createStatement();
        statement->execute("INSERT INTO TableVersions VALUES (\"TableVersions\", 1);");

        delete statement;
    }
}