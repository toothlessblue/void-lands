//
// Created by ellis on 17/05/22.
//

#pragma once
#include <cppconn/connection.h>
#include <cppconn/resultset.h>
#include <cppconn/driver.h>
#include <vector>
#include <map>
#include "TableBase.h"
#include "SQLGetter.h"
#include "Database/Description/Description.h"

namespace Database {
    extern sql::Driver* driver;
    extern sql::Connection* connection;
    extern std::vector<const TableBase*> tables;
    extern bool ready;

    void initialise();
    void destruct();
    void addTable(TableBase* table);

    bool execute(std::string query);
    bool execute(const char* query);
    sql::ResultSet* executeQuery(std::string query);
    sql::ResultSet* executeQuery(const char* query);

    std::map<std::string, DescriptionRow>* getTableColumns(const char* tableName);
}
