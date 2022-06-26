//
// Created by ellis on 24/05/22.
//


#pragma once

#include "Database/TableBase.h"
#include "Database/SQLGetter.h"
#include "Database/Database.h"

namespace Database {
    struct DamagesRow {
        int id;
        std::string worldId;
        float damage;
    };

    template<> class SQLGetter<DamagesRow> : public SQLGetterBase {
    public:
        SQLGetter(sql::ResultSet* results) : SQLGetterBase(results) {}

        DamagesRow getRow() {
            return {
                this->results->getInt("id"),
                this->results->getString("worldId"),
                static_cast<float>(this->results->getInt("damage"))
            };
        }
    };

    class Damages : public TableBase {
    private:
        static Damages instance;
        Damages();

    public:
        static Damages* getInstance();

        SQLGetter<DamagesRow> getDamagesForWorld(std::string worldId) {
            return Database::executeQuery<DamagesRow>("SELECT * FROM Damages WHERE worldId=\"" + worldId + "\";");
        }

        void loadIntoDataForWorld(DataStructure* data, std::string worldId) override;
        void saveDamage(DamagesRow row);
    };
}
