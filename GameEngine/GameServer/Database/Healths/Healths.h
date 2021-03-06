//
// Created by ellis on 24/05/22.
//


#pragma once

#include "Database/TableBase.h"
#include "Database/SQLGetter.h"
#include "Database/Database.h"

namespace Database {
    struct HealthsRow {
        int id;
        std::string worldId;
        float health;
    };

    template<> class SQLGetter<HealthsRow> : public SQLGetterBase {
    public:
        SQLGetter(sql::ResultSet* results) : SQLGetterBase(results) {}

        HealthsRow getRow() {
            return {
                this->results->getInt("id"),
                this->results->getString("worldId"),
                static_cast<float>(this->results->getInt("health"))
            };
        }
    };

    class Healths : public TableBase {
    private:
        static Healths instance;
        Healths();

    public:
        static Healths* getInstance();

        SQLGetter<HealthsRow> getHealthsForWorld(std::string worldId);

        void saveHealth(HealthsRow row);

        void loadIntoDataForWorld(DataStructure* data, std::string worldId) override;
    };
}
