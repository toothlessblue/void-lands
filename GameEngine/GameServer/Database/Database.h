//
// Created by ellis on 17/05/22.
//

#pragma once
#include <cppconn/connection.h>
#include <cppconn/driver.h>
#include <vector>
#include "TableBase.h"

namespace Database {
    extern sql::Driver* driver;
    extern sql::Connection* connection;
    extern std::vector<const TableBase*> tables;

    void initialise();
    void destruct();
    void addTable(TableBase* table);
    std::vector<char*> getTableColumns(const char* tableName);
}
