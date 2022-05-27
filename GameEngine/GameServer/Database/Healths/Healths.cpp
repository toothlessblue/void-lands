//
// Created by ellis on 24/05/22.
//

#include "Healths.h"

namespace Database {
    Healths Healths::instance;

    Healths::Healths() {
        this->name = "Healths";
        this->version = 1;
        this->primaryKey = "id,worldId";
        this->columns = {
            {"id",      "int",        ""},
            {"worldId", "varchar(50)",""},
            {"health",  "float",      ""}
        };
    }

    Healths* Healths::getInstance() {
        return &Healths::instance;
    }

    void Healths::saveHealth(HealthsRow row) {
        std::string values = std::string("(") + std::to_string(row.id) + ",\"" + row.worldId + "\"," + std::to_string(row.health) + ")";

        Database::execute(std::string() + "REPLACE INTO Healths (" + this->getColumnsAsString() + ") VALUES " + values + ";");
    }

    void Healths::loadIntoDataForWorld(DataStructure* data, std::string worldId) {
        SQLGetter<HealthsRow> getter = this->getHealthsForWorld(worldId);

        while (getter.next()) {
            HealthsRow row = getter.getRow();

            data->setMaxHealth(row.id, row.health);
        }
    }

    SQLGetter<HealthsRow> Healths::getHealthsForWorld(std::string worldId) {
        return Database::executeQuery<HealthsRow>("SELECT * FROM Healths WHERE worldId=\"" + worldId + "\";");
    }
}
