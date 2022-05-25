//
// Created by ellis on 24/05/22.
//


#pragma once

#include "Database/TableBase.h"
#include "Database/SQLGetter.h"
#include "Database/Database.h"

namespace Database {
    struct DropsRow {
        int id;
        std::string worldId;
        int itemId;
        int count;
    };

    template<> class SQLGetter<DropsRow> : public SQLGetterBase {
    public:
        SQLGetter(sql::ResultSet* results) : SQLGetterBase(results) {}

        DropsRow getRow() {
            return {
                this->results->getInt("id"),
                this->results->getString("worldId"),
                this->results->getInt("itemId"),
                this->results->getInt("count")
            };
        }
    };

    class Drops : public TableBase {
    private:
        static Drops instance;
        Drops();

    public:
        static Drops* getInstance();

        SQLGetter<DropsRow> getDropsForWorld(std::string worldId);

        void loadIntoDataForWorld(DataStructure* data, std::string worldId) override;
    };
}
