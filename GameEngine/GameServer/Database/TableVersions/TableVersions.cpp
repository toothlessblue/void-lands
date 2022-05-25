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
    TableVersions::TableVersions() {
        this->version = 1;
        this->name = "TableVersions";
        this->columns = {
            {"tableName", "VARCHAR(20)",  ""},
            {"version",   "INT UNSIGNED", ""},
        };
        this->primaryKey = "tableName";
    }
    TableVersions* TableVersions::getInstance() {
        return &TableVersions::instance;
    }
    int TableVersions::getVersion(const char* tableName) {
        if (!TableVersions::getInstance()->existsInDatabase()) return -1;
        std::string query = std::string("SELECT * FROM TableVersions WHERE tableName=\"") + tableName + "\";";
        SQLGetter<Database::TableVersionsRow> getter = Database::executeQuery<Database::TableVersionsRow>(query);
        int version = -1;
        if (getter.next()) {
            version = getter.getRow().version;
        }

        return version;
    }

    void TableVersions::setVersion(const char* tableName, unsigned int version) {
        Database::execute(std::string() +
            "INSERT INTO TableVersions VALUES (\"" + tableName + "\"," + std::to_string(version) + ") "
            "ON DUPLICATE KEY "
            "UPDATE tableName=\"" + tableName + "\", version=" + std::to_string(version) + ";"
        );
    }
}