//
// Created by ellis on 16/05/22.
//

#include "Worlds.h"

namespace Database {
    Worlds Worlds::instance;

    Worlds* Worlds::getInstance() {
        return &Worlds::instance;
    }

    Worlds::Worlds() {
        this->version = 3;
        this->name = "Worlds";
        this->columns = {
            {"worldId", "VARCHAR(50)", ""},
            {"isGenerated", "BOOLEAN", ""},
        };
        this->primaryKey = "id,worldId";
    }

    bool Worlds::isGenerated(std::string worldId) {
        SQLGetter<WorldsRow> getter = Database::executeQuery<WorldsRow>("SELECT * FROM Worlds WHERE worldId=\"" + worldId + "\"");

        if (getter.next()) {
            return getter.getRow().isGenerated;
        }

        return false;
    }

    void Worlds::saveWorld(WorldsRow row) {
        std::string values = "(\"" + row.worldId + "\"," + std::to_string(row.isGenerated) + ")";

        Database::execute("REPLACE INTO Worlds (" + this->getColumnsAsString() + ") VALUES " + values + ";");
    }


}
