//
// Created by ellis on 18/05/22.
//

#include "TableBase.h"
#include "Database.h"
#include "TableVersions/TableVersions.h"
#include <cppconn/statement.h>
#include <string>

namespace Database {
    unsigned int TableBase::getColumnCount() {
        return 0;
    }

    void TableBase::initialiseTable() {
        unsigned int version = TableVersions::getInstance()->getVersion(this->NAME);

        if (version == 0) {
            this->createTable();
        } else if (version < this->VERSION) {
            this->updateTable();
        }
    }

    void TableBase::createTable() {
        Column* columns = this->COLUMNS;
        unsigned int count = this->getColumnCount();

        std::string query = std::string("CREATE TABLE ") + this->NAME + " (";
        for (unsigned int i = 0; i < count; i++) {
            query += std::string() + columns[i].name + " " + columns[i].type + " " + columns[i].modifiers + ",";
        }
        query.pop_back(); // remove trailing comma
        query += ");";

        sql::Statement* statement = connection->createStatement();
        statement->execute(query);

        TableVersions::getInstance()->setVersion(this->NAME, this->VERSION);

        delete statement;
    }

    void TableBase::updateTable() {

    }

    bool TableBase::existsInDatabase() {
        sql::Statement* statement = connection->createStatement();
        sql::ResultSet* result = statement->executeQuery(
            std::string() + "SELECT * FROM information_schema.tables WHERE table_schema = 'db' AND table_name = '" +
            this->NAME + "';");

        bool exists = result->next();

        delete statement;
        delete result;

        return exists;
    }
}
