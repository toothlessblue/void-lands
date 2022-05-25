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
    struct WorldsRow {
        std::string worldId;
        bool isGenerated;
    };

    template<> class SQLGetter<WorldsRow> : public SQLGetterBase {
    public:
        SQLGetter(sql::ResultSet* results) : SQLGetterBase(results) {

        }

        WorldsRow getRow() {
            return {
                this->results->getString("worldId"),
                this->results->getBoolean("isGenerated"),
            };
        }
    };

    class Worlds : public TableBase {
    private:
        static Worlds instance;

        Worlds();

    public:
        static Worlds* getInstance();

        bool isGenerated(std::string worldId);
        void saveWorld(WorldsRow row);
    };
}

