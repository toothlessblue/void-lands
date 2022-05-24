//
// Created by ellis on 16/05/22.
//

#pragma once
#include "../TableBase.h"
#include "../SQLGetter.h"
#include "../Database.h"
#include <cppconn/statement.h>
#include <cppconn/resultset.h>

namespace Database {
    struct EntitiesRow {
        int id;
        std::string worldId;
        int type;
        float x;
        float z;
    };

    template<> class SQLGetter<EntitiesRow> : public SQLGetterBase {
    public:
        SQLGetter(sql::ResultSet* results) : SQLGetterBase(results) {

        }

        EntitiesRow getRow() {
            return {
                this->results->getInt("id"),
                this->results->getString("worldId"),
                this->results->getInt("type"),
                static_cast<float>(this->results->getInt("x")),
                static_cast<float>(this->results->getInt("z"))
            };
        }
    };

    class Entities : public TableBase {
    private:
        static Entities instance;

        Entities();

    public:
        static Entities* getInstance();

        SQLGetter<EntitiesRow> getEntitiesForWorld(std::string worldId);

        void saveEntity(EntitiesRow row);
    };
}

