//
// Created by ellis on 23/05/22.
//


#pragma once
#include <string>
#include <cppconn/resultset.h>
#include "../SQLGetter.h"

namespace Database {
    struct DescriptionRow {
        std::string field;
        std::string type;
        bool nullable;
        bool primary;
    };

    template<> class SQLGetter<DescriptionRow> : public SQLGetterBase {
    public:
        SQLGetter(sql::ResultSet* results) : SQLGetterBase(results) {

        }

        DescriptionRow getRow() {
            return {
                this->results->getString("Field"),
                this->results->getString("Type"),
                this->results->getString("Null") == "YES",
                this->results->getString("Key") == "PRI"
            };
        }
    };
}