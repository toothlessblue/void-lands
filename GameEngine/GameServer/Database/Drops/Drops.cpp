//
// Created by ellis on 24/05/22.
//

#include "Drops.h"

namespace Database {
    Drops Drops::instance;

    Drops::Drops() {
        this->name = "Drops";
        this->version = 1;
        this->primaryKey = "id,worldId,itemId";
        this->columns = {
            {"id",      "int",        ""},
            {"worldId", "varchar(50)",""},
            {"itemId",  "int",        ""},
            {"count",   "int",        ""}
        };
    }

    Drops* Drops::getInstance() {
        return &Drops::instance;
    }

    SQLGetter<DropsRow> Drops::getDropsForWorld(std::string worldId) {
        return Database::executeQuery<DropsRow>("SELECT * FROM Drops WHERE worldId=\"" + worldId + "\";");
    }

    void Drops::loadIntoDataForWorld(DataStructure* data, std::string worldId) {
        SQLGetter<DropsRow> getter = this->getDropsForWorld(worldId);

        while (getter.next()) {
            DropsRow row = getter.getRow();

            data->addResource(row.id, row.itemId, row.count);
        }
    }
}
