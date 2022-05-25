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
            {"damage",  "float",      ""}
        };
    }

    Healths* Healths::getInstance() {
        return &Healths::instance;
    }

    void Healths::saveHealth(HealthsRow row) {
        std::string values = std::string("(") + std::to_string(row.id) + ",\"" + row.worldId + "\"," + std::to_string(row.health) + ")";

        Database::execute(std::string() + "REPLACE INTO Entities (" + this->getColumnsAsString() + ") VALUES " + values + ";");
    }
}
