//
// Created by ellis on 16/05/22.
//

#pragma once
#include "../TableBase.h"
#include <cppconn/statement.h>
#include <cppconn/resultset.h>

namespace Database {
    class Entities : public TableBase {
    private:
        static Entities instance;

        Entities();

    public:
        static Entities* getInstance();

        struct Row {
            int id;
            std::string worldId;
            int type;
            float posX;
            float posZ;
        };
    };
}

class SQLGetter {
protected:
    sql::ResultSet* results;


};

template<typename T>
class SQLGetter : public SQLGetterBase {

public:
    SQLGetter() {

    }

    ~SQLGetter() {

    }

    T next();
};

class SQLGetter<Database::Entities::Row> : public SQLGetterBase {
public:
    Database::Entities::Row next() {
        if (!this->res)

        return {

        }
    }
};