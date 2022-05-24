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
        return SQLGetter<EntitiesRow>(Database::executeQuery("SELECT * FROM Entities WHERE worldId=\"" + worldId + "\";"));
    }
}
