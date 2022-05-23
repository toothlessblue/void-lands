//
// Created by ellis on 17/05/22.
//

#include "Database.h"
#include "Entities/Entities.h"
#include "TableVersions/TableVersions.h"
#include "Logger/Logger.h"
#include <cppconn/statement.h>
#include <vector>

sql::Driver* Database::driver;
sql::Connection* Database::connection;
std::vector<const Database::TableBase*> Database::tables;

namespace Database {
    void initialise() {
        driver = get_driver_instance();
        connection = driver->connect("127.0.0.1:3306", "server", "7Q*eH-b_5su.8mBV");
        connection->setSchema("db");

        addTable(TableVersions::getInstance());
        addTable(Entities::getInstance());
    }

    void destruct() {
        delete connection;
        tables.clear();
    }

    void addTable(TableBase* table) {
        tables.push_back(table);
        table->initialiseTable();
    }

    std::vector<char*> getTableColumns(const char* tableName) {
        return {};
    }

    bool execute(const char* query) {
        Logger::Debug() << "Executing query: " << query;

        sql::Statement* statement = connection->createStatement();
        bool result = statement->execute(query);
        delete statement;

        return result;

    }

    bool execute(std::string query) {
        return execute(&query[0]);
    }

    sql::ResultSet* executeQuery(const char* query) {
        Logger::Debug() << "Executing query: " << query;

        sql::Statement* statement = connection->createStatement();
        sql::ResultSet* result = statement->executeQuery(query);

        delete statement;

        return result;
    }

    sql::ResultSet* executeQuery(std::string query) {
        return executeQuery(&query[0]);
    }
}