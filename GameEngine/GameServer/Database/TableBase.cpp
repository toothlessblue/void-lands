//
// Created by ellis on 18/05/22.
//

#include "TableBase.h"
#include "Database.h"
#include "TableVersions/TableVersions.h"
#include "Logger/Logger.h"
#include <cppconn/statement.h>
#include <string>

namespace Database {
    void TableBase::initialiseTable() {
        unsigned int databaseVersion = TableVersions::getInstance()->getVersion(this->name);

        if (databaseVersion == 0) {
            this->createTable();
        } else if (databaseVersion < this->version) {
            this->updateTable();
        } else if (databaseVersion > this->version) {
            throw std::runtime_error(std::string() + "Database has '" + this->name + "' version " + std::to_string(databaseVersion) + ", but code is version " + std::to_string(this->version));
            // TODO program should fail here with an "out of date database" message
        }
    }

    void TableBase::createTable() {
        std::string query = std::string("CREATE TABLE ") + this->name + " (";
        for (unsigned int i = 0; i < this->columns.size(); i++) {
            query += std::string() + this->columns[i].name + " " + this->columns[i].type + " " + this->columns[i].modifiers + ",";
        }
        if (this->primaryKey.size()) query += std::string() + "PRIMARY KEY (" + this->primaryKey + "),";
        query.pop_back(); // remove trailing comma
        query += ");";

        Database::execute(query);

        TableVersions::getInstance()->setVersion(this->name, this->version);
    }

    void TableBase::updateTable() {

    }

    bool TableBase::existsInDatabase() {
        if (!this->existenceChecked) {
            sql::ResultSet* result = Database::executeQuery(
                std::string() + "SELECT * FROM information_schema.tables WHERE table_schema = 'db' AND table_name = '" +
                this->name + "';");

            this->exists = result->next();
            this->existenceChecked = true;

            delete result;
        }

        return this->exists;
    }

    void TableBase::compareTables() {

    }
}
