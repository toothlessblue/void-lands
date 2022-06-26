//
// Created by ellis on 24/05/22.
//

#include "Damages.h"

namespace Database {
    Damages Damages::instance;

    Damages::Damages() {
        this->name = "Damages";
        this->version = 1;
        this->primaryKey = "id,worldId";
        this->columns = {
            {"id",      "int",        ""},
            {"worldId", "varchar(50)",""},
            {"damage",  "float",      ""}
        };
    }

    Damages* Damages::getInstance() {
        return &Damages::instance;
    }

    void Damages::loadIntoDataForWorld(DataStructure* data, std::string worldId) {
        SQLGetter<DamagesRow> getter = this->getDamagesForWorld(worldId);

        while (getter.next()) {
            DamagesRow row = getter.getRow();

            data->setDamage(row.id, row.damage);
        }
    }

    void Damages::saveDamage(DamagesRow row) {
        std::string values = std::string("(") + std::to_string(row.id) + ",\"" + row.worldId + "\"," + std::to_string(row.damage) + ")";

        Database::execute(std::string() + "REPLACE INTO Damages (" + this->getColumnsAsString() + ") VALUES " + values + ";");
    }
}
