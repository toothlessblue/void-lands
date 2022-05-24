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

        SQLGetter<HealthsRow> getHealthsForWorld(std::string worldId) {
            return SQLGetter<HealthsRow>(Database::executeQuery("SELECT * FROM Healths WHERE worldId=\"" + worldId + "\";"));
        }

        void saveHealth(HealthsRow row) {
            std::string values = std::string("(") + std::to_string(row.id) + ",\"" + row.worldId + "\"," + std::to_string(row.health) + ")";

            Database::execute(std::string() + "REPLACE INTO Entities (" + this->getColumnsAsString() + ") VALUES " + values + ";");
        }
    };
}
