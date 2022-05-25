//
// Created by ellis on 17/05/22.
//

#include "Database.h"
#include "Entities/Entities.h"
#include "TableVersions/TableVersions.h"
#include "Healths/Healths.h"
#include "Logger/Logger.h"
#include "Database/Damages/Damages.h"
#include "Database/Drops/Drops.h"
#include <cppconn/statement.h>
#include <vector>

sql::Driver* Database::driver;
sql::Connection* Database::connection;
std::vector<Database::TableBase*> Database::tables;
bool Database::ready = false;

namespace Database {
    void initialise() {
        if (Database::ready) return;

        Database::driver = get_driver_instance();
        Database::connection = driver->connect("127.0.0.1:3306", "server", "7Q*eH-b_5su.8mBV");
        Database::connection->setSchema("db");

        Database::addTable(TableVersions::getInstance());
        Database::addTable(Entities::getInstance());
        Database::addTable(Healths::getInstance());
        Database::addTable(Damages::getInstance());
        Database::addTable(Drops::getInstance());

        Database::ready = true;
    }

    void destruct() {
        Database::connection->close();
        delete connection;
        tables.clear();
    }

    void addTable(TableBase* table) {
        tables.push_back(table);
        table->initialiseTable();
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

    std::map<std::string, DescriptionRow>* getTableColumns(const char* tableName) {
        std::map<std::string, DescriptionRow>* attributesWithinDb = new std::map<std::string, DescriptionRow>();

        SQLGetter<DescriptionRow> tableQuery = Database::executeQuery<Database::DescriptionRow>(std::string() + "describe " + tableName + ";");

        while (tableQuery.next()) {
            DescriptionRow row = tableQuery.getRow();
            attributesWithinDb->insert({row.field, row});
        }

        return attributesWithinDb;
    }

    sql::ResultSet* executeQueryRaw(const char* query) {
        Logger::Debug() << "Executing query: " << query;

        sql::Statement* statement = connection->createStatement();
        sql::ResultSet* result = statement->executeQuery(query);

        delete statement;

        return result;
    }

    sql::ResultSet* executeQueryRaw(std::string query) {
        return executeQueryRaw(&query[0]);
    }
}