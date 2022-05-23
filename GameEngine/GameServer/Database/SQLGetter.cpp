//
// Created by ellis on 23/05/22.
//

#include "SQLGetter.h"

namespace Database {
    SQLGetterBase::SQLGetterBase(sql::ResultSet* results) {
        this->results = results;
    }

    SQLGetterBase::~SQLGetterBase() {
        delete this->results;
    }

    bool SQLGetterBase::next() {
        return this->results->next();
    }
}