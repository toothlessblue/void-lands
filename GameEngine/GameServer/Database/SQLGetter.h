//
// Created by ellis on 23/05/22.
//


#pragma once

#include <cppconn/resultset.h>

namespace Database {
    class SQLGetterBase {
    protected:
        sql::ResultSet* results;

    public:
        SQLGetterBase(sql::ResultSet* results);
        ~SQLGetterBase();
        bool next();
    };

    template<typename T>
    class SQLGetter : public SQLGetterBase {
    public:
        SQLGetter(sql::ResultSet* results) : SQLGetterBase(results) {}
        T getRow();
    };
}