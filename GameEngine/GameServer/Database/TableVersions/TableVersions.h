//
// Created by ellis on 18/05/22.
//


#pragma once
#include "../TableBase.h"
#include "Database/SQLGetter.h"
#include <cppconn/statement.h>
#include <cppconn/resultset.h>

namespace Database {
    struct TableVersionsRow {
        std::string tableName;
        unsigned int version;
    };

    template<> class SQLGetter<TableVersionsRow> : public SQLGetterBase {
    public:
        SQLGetter(sql::ResultSet* results) : SQLGetterBase(results) {

        }

        TableVersionsRow getRow() {
            return {
                this->results->getString("tableName"),
                this->results->getUInt("version"),
            };
        }
    };

    class TableVersions : public TableBase {
    private:
        static TableVersions instance;

        TableVersions();
    public:
        static TableVersions* getInstance();

        int getVersion(const char* tableName);
        void setVersion(const char* tableName, unsigned int version);
    };
}
