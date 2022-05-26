//
// Created by ellis on 16/05/22.
//

#include "Entities.h"

namespace Database {
    Entities Entities::instance;

    Entities* Entities::getInstance() {
        return &Entities::instance;
    }

    Entities::Entities() {
        this->version = 3;
        this->name = "Entities";
        this->columns = {
            {"id",      "INT",         ""},
            {"worldId", "VARCHAR(50)", ""},
            {"type",    "INT",         ""},
            {"x",       "FLOAT",       ""},
            {"z",       "FLOAT",       ""},
        };
        this->primaryKey = "id,worldId";
    }

    SQLGetter<EntitiesRow> Entities::getEntitiesForWorld(std::string worldId) {
        return Database::executeQuery<EntitiesRow>("SELECT * FROM Entities WHERE worldId=\"" + worldId + "\";");
    }

    void Entities::saveEntity(EntitiesRow row) {
        std::string values = std::string("(") + std::to_string(row.id) + ",\"" + row.worldId + "\"," + std::to_string(row.type) + "," + std::to_string(row.x) + "," + std::to_string(row.z) + ")";

        Database::execute(std::string() + "REPLACE INTO Entities (" + this->getColumnsAsString() + ") VALUES " + values + ";");
    }

    void Entities::loadIntoDataForWorld(DataStructure* data, std::string worldId) {
        SQLGetter<EntitiesRow> getter = this->getEntitiesForWorld(worldId);

        while (getter.next()) {
            EntitiesRow row = getter.getRow();

            data->addEntity(row.id, row.type, row.x, row.z);
        }
    }

    int Entities::getNextEntityId(std::string worldId) {
        sql::ResultSet* result = Database::executeQueryRaw("SELECT MAX(id) AS Next FROM Entities WHERE worldId=\"" + worldId + "\";");

        if (!result->next()) return -1;

        int id = result->getInt("Next");
        delete result;
        return id + 1;
    }
}
