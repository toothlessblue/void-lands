//
// Created by ellis on 17/05/22.
//

#pragma once
#include <cppconn/connection.h>
#include <cppconn/resultset.h>
#include <cppconn/driver.h>
#include <vector>
#include "TableBase.h"
#include "SQLGetter.h"

namespace Database {
    extern sql::Driver* driver;
    extern sql::Connection* connection;
    extern std::vector<const TableBase*> tables;

    void initialise();
    void destruct();
    void addTable(TableBase* table);

    bool execute(std::string query);
    bool execute(const char* query);
    sql::ResultSet* executeQuery(std::string query);
    sql::ResultSet* executeQuery(const char* query);

    std::vector<char*> getTableColumns(const char* tableName);
}
